#include <iostream>
#include <Windows.h>
#include <string>
#include "resource.h"

/* EVENT HANDLER DEFINES */

#define WM_NOTIFICATIONICON				(WM_USER+1)
#define WM_CHANGEBG						(WM_USER+2)
#define WM_SETTIMER						(WM_USER+3)
#define WM_SETSUBREDDIT					(WM_USER+4)

/* END EVENT HANDLER DEFINES */

// create and set the icon in the notification bar
NOTIFYICONDATAA setIcon(HINSTANCE instance, HWND messageWindow);

// create the window to handle the messages from Windows
HWND createMessageWindow(WNDPROC messageCallback);

// create the context menu for the icon
HMENU initIconContextMenu(HINSTANCE instance, int interval, std::string subreddit);

// display the context menu. Return the id of the item clicked
int displayContextMenu(HMENU menu, int x, int y, HWND msgWindow);

// manage the context menu of the icon. Return false if you should close the menu
bool manageIconContextMenu(HMENU menu, HWND messageWindow, int menuId);

void editCurrentTimer(HMENU menu, int interval);

void editCurrentSubreddit(HMENU menu, std::string subreddit);

std::string getCheckedSubreddit(HMENU menu);