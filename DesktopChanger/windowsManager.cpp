#pragma once
#include "windowsManager.h"


NOTIFYICONDATAA setIcon(HINSTANCE instance, HWND messageWindow)
{
	NOTIFYICONDATAA nid;
	nid.cbSize = sizeof(nid);
	nid.uID = UID_ICON1;
	nid.hWnd = messageWindow;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = WM_NOTIFICATIONICON;
	nid.hIcon = LoadIconA(instance, MAKEINTRESOURCEA(IDI_ICON1));
	nid.uVersion = NOTIFYICON_VERSION_4;
	strncpy_s(nid.szTip, 128, "Desktop Changer", 128);

	Shell_NotifyIconA(NIM_ADD, &nid);
	Shell_NotifyIconA(NIM_SETVERSION, &nid);

	return nid;
}

HWND createMessageWindow(WNDPROC messageCallback)
{
	HWND messageWindow;
	WNDCLASSA winClass = {};
	winClass.lpfnWndProc = messageCallback;
	winClass.hInstance = GetModuleHandleA(NULL);
	winClass.lpszClassName = "messageClass";
	RegisterClassA(&winClass);

	// needed to handle the icon
	messageWindow = CreateWindowExA(0, winClass.lpszClassName, "message", 0, 0, 0, 0, 0, HWND_MESSAGE, 0, 0, 0);

	return messageWindow;
}

HMENU initIconContextMenu(HINSTANCE instance, int interval, std::string subreddit)
{
	// load menu
	HMENU menu = LoadMenuA(instance, MAKEINTRESOURCEA(IDR_MENU1));
	menu = GetSubMenu(menu, 0);

	// set default timer
	editCurrentTimer(menu, interval);

	editCurrentSubreddit(menu, subreddit);

	return menu;
}

int displayContextMenu(HMENU menu, int x, int y, HWND window)
{
	SetForegroundWindow(window); // needed to make the menu disappear after use
	UINT flags = TPM_LEFTALIGN | TPM_BOTTOMALIGN | TPM_RIGHTBUTTON | TPM_VERNEGANIMATION | TPM_RETURNCMD;
	int id = TrackPopupMenu(menu,flags, x, y, 0, window, 0);

	return id;
}

void toggleCheckTimers(HMENU menu, int menuId)
{
	int state;
	// uncheck all the timers
	// TODO i hope the defines don't change
	for (int i = MENU_1MIN; i <= MENU_120MIN; i++)
	{
		//state = GetMenuState(menu, i, MF_CHECKED);
		//if (state & MF_CHECKED)
			CheckMenuItem(menu, i, MF_BYCOMMAND | MF_UNCHECKED);
	}
	// check the current timer
	state = GetMenuState(menu, menuId, MF_CHECKED);
	if (state & MF_CHECKED)
		CheckMenuItem(menu, menuId, MF_BYCOMMAND | MF_UNCHECKED);
	else
		CheckMenuItem(menu, menuId, MF_BYCOMMAND | MF_CHECKED);
}

void toggleCheckSubreddit(HMENU menu, int menuId)
{
	int state = GetMenuState(menu, menuId, MF_CHECKED);
	if (state & MF_CHECKED)
		CheckMenuItem(menu, menuId, MF_BYCOMMAND | MF_UNCHECKED);
	else
		CheckMenuItem(menu, menuId, MF_BYCOMMAND | MF_CHECKED);
}

bool manageIconContextMenu(HMENU menu, HWND messageWindow, int menuId)
{
	bool open = false;
	switch (menuId)
	{
		case MENU_EXIT:
		{
			PostMessageA(messageWindow, WM_QUIT, 0, 0);
		} break;
		case MENU_CHANGE_BG:
		{
			PostMessageA(messageWindow, WM_CHANGEBG, 0, 0);
		} break;
		case MENU_1MIN:
		{
			PostMessageA(messageWindow, WM_SETTIMER, 0, 1);
			toggleCheckTimers(menu, menuId);
			//open = true;
		} break;
		case MENU_5MIN:
		{
			PostMessageA(messageWindow, WM_SETTIMER, 0, 5);
			toggleCheckTimers(menu, menuId);
			//open = true;
		} break;
		case MENU_10MIN:
		{
			PostMessageA(messageWindow, WM_SETTIMER, 0, 10);
			toggleCheckTimers(menu, menuId);
			//open = true;
		} break;
		case MENU_20MIN:
		{
			PostMessageA(messageWindow, WM_SETTIMER, 0, 20);
			toggleCheckTimers(menu, menuId);
			//open = true;
		} break;
		case MENU_30MIN:
		{
			PostMessageA(messageWindow, WM_SETTIMER, 0, 30);
			toggleCheckTimers(menu, menuId);
			//open = true;
		} break;
		case MENU_60MIN:
		{
			PostMessageA(messageWindow, WM_SETTIMER, 0, 60);
			toggleCheckTimers(menu, menuId);
			//open = true;
		} break;
		case MENU_120MIN:
		{
			PostMessageA(messageWindow, WM_SETTIMER, 0, 120);
			toggleCheckTimers(menu, menuId);
			//open = true;
		} break;
		case MENU_SUBREDDIT_1:
		{
			toggleCheckSubreddit(menu, MENU_SUBREDDIT_1);
			std::string subreddit = getCheckedSubreddit(menu);
			editCurrentSubreddit(menu, subreddit);
			SendMessageA(messageWindow, WM_SETSUBREDDIT,0,(LPARAM) subreddit.c_str());
		} break;
		case MENU_SUBREDDIT_2:
		{
			toggleCheckSubreddit(menu, MENU_SUBREDDIT_2);
			std::string subreddit = getCheckedSubreddit(menu);
			editCurrentSubreddit(menu, subreddit);
			SendMessageA(messageWindow, WM_SETSUBREDDIT, 0, (LPARAM)subreddit.c_str());
		} break;
		case MENU_SUBREDDIT_3:
		{
			toggleCheckSubreddit(menu, MENU_SUBREDDIT_3);
			std::string subreddit = getCheckedSubreddit(menu);
			editCurrentSubreddit(menu, subreddit);
			SendMessageA(messageWindow, WM_SETSUBREDDIT, 0, (LPARAM)subreddit.c_str());
		} break;
		case MENU_SUBREDDIT_4:
		{
			toggleCheckSubreddit(menu, MENU_SUBREDDIT_4);
			std::string subreddit = getCheckedSubreddit(menu);
			editCurrentSubreddit(menu, subreddit);
			SendMessageA(messageWindow, WM_SETSUBREDDIT, 0, (LPARAM)subreddit.c_str());
		} break;
		case MENU_SUBREDDIT_5:
		{
			toggleCheckSubreddit(menu, MENU_SUBREDDIT_5);
			std::string subreddit = getCheckedSubreddit(menu);
			editCurrentSubreddit(menu, subreddit);
			SendMessageA(messageWindow, WM_SETSUBREDDIT, 0, (LPARAM)subreddit.c_str());
		} break;
		case MENU_SUBREDDIT_6:
		{
			toggleCheckSubreddit(menu, MENU_SUBREDDIT_6);
			std::string subreddit = getCheckedSubreddit(menu);
			editCurrentSubreddit(menu, subreddit);
			SendMessageA(messageWindow, WM_SETSUBREDDIT, 0, (LPARAM)subreddit.c_str());
		} break;
		case MENU_SUBREDDIT_7:
		{
			toggleCheckSubreddit(menu, MENU_SUBREDDIT_7);
			std::string subreddit = getCheckedSubreddit(menu);
			editCurrentSubreddit(menu, subreddit);
			SendMessageA(messageWindow, WM_SETSUBREDDIT, 0, (LPARAM)subreddit.c_str());
		} break;
		case MENU_SUBREDDIT_8:
		{
			toggleCheckSubreddit(menu, MENU_SUBREDDIT_8);
			std::string subreddit = getCheckedSubreddit(menu);
			editCurrentSubreddit(menu, subreddit);
			SendMessageA(messageWindow, WM_SETSUBREDDIT, 0, (LPARAM)subreddit.c_str());
		} break;
		case MENU_SUBREDDIT_9:
		{
			toggleCheckSubreddit(menu, MENU_SUBREDDIT_9);
			std::string subreddit = getCheckedSubreddit(menu);
			editCurrentSubreddit(menu, subreddit);
			SendMessageA(messageWindow, WM_SETSUBREDDIT, 0, (LPARAM)subreddit.c_str());
		} break;
		default:
			break;
	} /* switch(menuId) */

	return open;
}

void editCurrentTimer(HMENU menu, int interval)
{
	char currentTimerString[100];
	sprintf_s(currentTimerString, 100, "Current timer: %d minutes", interval / 60000);
	ModifyMenuA(menu, MENU_CURRENTTIMER, MF_BYCOMMAND | MF_STRING | MF_DISABLED | MF_GRAYED, MENU_CURRENTTIMER, currentTimerString);
}

void editCurrentSubreddit(HMENU menu, std::string subreddit)
{
	char currentSubrString[250];
	sprintf_s(currentSubrString, 250, "Current subreddit: %s", subreddit.c_str());
	ModifyMenuA(menu, MENU_CURRENTSUBREDDIT, MF_BYCOMMAND | MF_STRING | MF_DISABLED | MF_GRAYED, MENU_CURRENTTIMER, currentSubrString);
}

std::string getCheckedSubreddit(HMENU menu)
{
	int state;
	char temp[250];
	std::string subreddit = "";
	// TODO defines could change
	for (int i = MENU_SUBREDDIT_1; i <= MENU_SUBREDDIT_9; i++)
	{
		state = GetMenuState(menu, i, MF_CHECKED);
		if (state != -1 && state & MF_CHECKED)
		{
			GetMenuStringA(menu, i, temp, 250, MF_BYCOMMAND);
			subreddit += temp;
			subreddit += "+";
		}
		state = 0;
	}
	return subreddit;
}