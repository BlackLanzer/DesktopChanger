#include <iostream>
#include <Windows.h>
#include <string>

const std::string DEFAULT_SUBREDDIT = "earthporn+skyporn";
const int DEFAULT_INTERVAL = 1800000;

int interval = DEFAULT_INTERVAL;
std::string subreddit = DEFAULT_SUBREDDIT;

std::wstring ExePath() {
	wchar_t buffer[MAX_PATH];
	GetModuleFileNameW(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos + 1);
}


int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	int argc = __argc;
	bool exec = true; // if i don't want to change background
	std::wstring pathDl = ExePath() + L"download";

	// create download folder before calling the other process
	// so we see the console only once :)
	//if (!(GetFileAttributesA("download") & FILE_ATTRIBUTE_DIRECTORY))
	_wmkdir(pathDl.c_str());


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
				interval = atoi(__argv[i]) * 60000;
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
