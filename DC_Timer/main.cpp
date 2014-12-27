#include <iostream>
#include <Windows.h>

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	// create download folder before calling the other process
	// so we see the console only once :)
	_wmkdir(L"download");
	// default settings: SUBREDDIT_DEFAULTS, half hour change
	if (__argc == 1) // default settings
	{
		while (true)
		{
			WinExec("DesktopChanger.exe", SW_HIDE);
			Sleep(1800000);
		}
	}
}
