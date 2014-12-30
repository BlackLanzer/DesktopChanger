#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include "Timer.h"
#include "JsonManager.h"
#include "BackgroundImg.h"
#include "InternetManager.h"

#define SUBREDDIT_DEFAULT "earthporn+skyporn"


BackgroundImg BackFromUrl(std::string url)
{
	return BackgroundImg("background", url.substr(url.length() - 4, url.npos));
}

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	std::string subreddit = __argc > 1 ? __argv[1] : SUBREDDIT_DEFAULT;

	InternetManager inetMan;
	JsonManager jsonMan;

	// create folder to download the wallpaper
	//WinExec("mkdir download", SW_HIDE);
	//system("mkdir download");
	//_wmkdir(L"download");

	// get and parse json page from reddit
	char* jsonPage = NULL;
	inetMan.DownloadPage(subreddit, &jsonPage);
	jsonMan.setInput(jsonPage);
	jsonMan.parseInput();

	// if it doesn't find urls exit
	if (jsonMan.getUrlN() == 0)
		return 0;

	// random and download the background
	srand(time(NULL));
	int indexRand = rand() % jsonMan.getUrlN();
	std::string urlImg = jsonMan.getUrl(indexRand);
	_RPT3(0, "Random: %d/%d, Url: %s\n", indexRand, jsonMan.getUrlN(), urlImg.c_str());
	BackgroundImg back = BackFromUrl(urlImg);
	std::string imgPath = std::string("download\\background") + back.extension;
	// if the download fail exit
	if (inetMan.DownloadFile(urlImg, imgPath) != S_OK)
		return 0;
	_RPT1(0, "File downloaded in %s\n", imgPath.c_str());

	// build the absolute path of image, because Windows API sucks
	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	strcat_s(path, MAX_PATH, "\\");
	imgPath = path + imgPath;

	// set new background
	_RPT1(0, "Path: %s\n", imgPath.c_str());
	SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)imgPath.c_str(), SPIF_UPDATEINIFILE);

	// reset and delete things
	//jsonMan.reset();
	delete jsonPage;

	return 0;
}