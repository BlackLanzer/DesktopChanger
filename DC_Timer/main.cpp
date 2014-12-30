#include <iostream>
#include <Windows.h>
#include <string>

const std::string DEFAULT_SUBREDDIT = "earthporn+skyporn";
const int DEFAULT_INTERVAL = 18000;

int interval = DEFAULT_INTERVAL;
std::string subreddit = DEFAULT_SUBREDDIT;

int main(int argc, char* argv[])
{
	//int argc = __argc;
	bool exec = true; // if i don't want to change background for debugging

	//ShowWindow(hwnd_win, SW_HIDE);
	// create download folder before calling the other process
	// so we see the console only once :)
	if (!(GetFileAttributesA("download") & FILE_ATTRIBUTE_DIRECTORY))
		_wmkdir(L"download");

	// default settings: SUBREDDIT_DEFAULTS, half hour change
	if (argc != 1) // default settings
	{
		char menu[500];
		for (int i = 1; i < argc; i++)
		{
			strcpy_s(menu, 500, __argv[i++]);

			switch (menu[1])
			{
			case 't':
				interval = atoi(__argv[i]);
				if (interval == 0)
					interval = DEFAULT_INTERVAL;
				break;
			case 's':
				subreddit = __argv[i];
				break;
			case 'n':
				exec = false;
				break;
			default:
				break;
			}
		}

	}
	while (exec)
	{
		WinExec(std::string("DesktopChanger.exe " + subreddit).c_str(), SW_HIDE);
		
		Sleep(interval);
	}
	return 0;
}

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	int argc = __argc;
	bool exec = true; // if i don't want to change background
	
	std::cout << "The console will now close\n";
	HWND hwnd_win = GetForegroundWindow();
	ShowWindow(hwnd_win, SW_HIDE);

	// create download folder before calling the other process
	// so we see the console only once :)
	if (!(GetFileAttributesA("download") & FILE_ATTRIBUTE_DIRECTORY))
		_wmkdir(L"download");

	// default settings: SUBREDDIT_DEFAULTS, half hour change
	if (argc != 1) // default settings
	{
		char menu[500];
		for (int i = 1; i < argc; i++)
		{
			strcpy_s(menu, 500,__argv[i++]);

			switch (menu[1])
			{
			case 't':
				interval = atoi(__argv[i]);
				if (interval == 0)
					interval = DEFAULT_INTERVAL;
				break;
			case 's':
				subreddit = __argv[i];
				break;
			case 'n':
				exec = false;
				break;
			default:
				break;
			}
		}
		
	}
	while (exec)
	{
			WinExec(std::string("DesktopChanger.exe " + subreddit).c_str(), SW_HIDE);
			Sleep(interval);
	}
	return 0;
}
