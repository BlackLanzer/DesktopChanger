#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <string>
#include "BackgroundImg.h"
#include "InternetManager.h"
#include "misc.h"
#include "DesktopChanger.h"
#include "resource.h"
#include "windowsManager.h"
#include <windowsx.h>
#include <thread>

const std::string DEFAULT_SUBREDDIT = "earthporn+skyporn+wallpaper";
const int DEFAULT_INTERVAL = 1800000;

HWND messageWindow; // needed to handle the system messages (icon and timer)
NOTIFYICONDATAA nid; // needed to create and delete the icon
HMENU iconMenu = NULL; // the context menu of the icon
int timerId;
bool changeDesktop; // for debugging purpose
bool persistent; // true for keeping the process alive
int interval;
std::string subreddit;

/* WINDOWS MESSAGES HANDLER */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg)
	{
		case WM_NOTIFICATIONICON:
		{
			WORD x = HIWORD(lParam);
			if (LOWORD(lParam) == WM_CONTEXTMENU)
			{
				int x = GET_X_LPARAM(wParam);
				int y = GET_Y_LPARAM(wParam);
				int menuId;
				do
				{
					menuId = displayContextMenu(iconMenu, x, y, messageWindow);
				} while (manageIconContextMenu(iconMenu, messageWindow, menuId));
			}
		} break;
		case WM_CHANGEBG:
		{
			changeDesktop = true;
		} break;
		case WM_SETTIMER:
		{
			interval = lParam * 2000;//60000;
			SetTimer(messageWindow, timerId, interval, NULL);
		} break;
		case WM_SETSUBREDDIT:
		{
			subreddit = (char*)lParam;
		} break;
		case WM_TIMER:
		{
			// TODO changeDesktop = true;
		} break;
		case WM_DESTROY:
		{
			Shell_NotifyIconA(NIM_DELETE, &nid);
			_RPT0(0, "destroy\n");
		} break;
		case WM_QUIT:
		{
			persistent = false;
		} break;
		default:
			result = DefWindowProcA(hwnd, uMsg, wParam, lParam);
			break;
	} /* switch(uMsg) */

	return result;
}



int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	/* GLOBAL VARIABLES */

	changeDesktop = true;
	persistent = true;
	interval = DEFAULT_INTERVAL;
	subreddit = DEFAULT_SUBREDDIT;

	/* END GLOBAL VARIABLES */

	/* ENTRY POINT */

	MSG message;
	int argc = __argc;
	bool setDesktop = true;
	

	/* BEGIN PARAMETERS HANDLING */
	/* DesktopChanger [-t interval] [-s subreddit] [-d] */
	if (argc != 1)
	{
		char menu[500];
		for (int i = 1; i < argc; i++)
		{
			strcpy_s(menu, 500, __argv[i]);

			switch (menu[1])
			{
				case 't':
				{
					interval = atoi(__argv[++i]) * 60000;
					if (interval == 0)
						interval = DEFAULT_INTERVAL;
				} break;
				case 's':
				{
					subreddit = __argv[++i];
				} break;
				case 'd':
				{
					setDesktop = false;
					changeDesktop = false;
				} break;
				case 'c':
				{
					persistent = false;
				} break;
				default:
					break;
				}
		}
	}
	/* END PARAMETERS HANDLING */

	if (persistent) // create icon and timer only if wanted
	{
		messageWindow = createMessageWindow(WindowProc);
		nid = setIcon(hInstance,messageWindow);
		iconMenu = initIconContextMenu(hInstance,interval,subreddit);
		timerId = SetTimer(messageWindow, 0, interval, NULL);
	}

	do
	{
		// check for windows messages (timer and icon)
		while (PeekMessageA(&message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		// download and set new desktop
		if (changeDesktop)
		{
			changeDesktop = false;
			std::string imgUrl = getImageUrlFromReddit(subreddit);
			std::string imgPath;
			if ((imgPath = downloadImage(imgUrl)) != "")
			{
				if (setDesktop)
					setBackground(imgPath);
			}
		}
		
	} while (persistent);

	// destroy the message window to delete the icon
	DestroyWindow(messageWindow);

	return 0;
}