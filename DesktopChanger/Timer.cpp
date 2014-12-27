#include "Timer.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include "BackgroundImg.h"
#include "InternetManager.h"


Timer::Timer(int i)
{
	interval = i*1000;
	go = true;
	inetMan = InternetManager();
	jsonMan = JsonManager();
	GetCurrentDirectoryA(MAX_PATH, exePath);
	lstrcat(exePath, "\\");
}

Timer::Timer() : Timer::Timer(1)
{ }


Timer::~Timer()
{
	delete _thread;
}

bool Timer::Start()
{
	_thread = new std::thread(&Timer::InitTimer, this);
	_thread->detach();
	return true;
}

void Timer::Stop()
{
	go = false;
}

// function that does the things
void Timer::Init()
{
	// create folder to download the wallpaper
	system("@echo off\nmkdir download");

	//while (go)
	{
		_RPT0(0, "refresh\n");

		// get and parse json page from reddit
		char* jsonPage = NULL;
		inetMan.DownloadPage("earthporn+skyporn",&jsonPage);
		jsonMan.setInput(jsonPage);
		jsonMan.parseInput();

		// random and download the background
		srand(time(NULL));
		int indexRand = rand() % jsonMan.getUrlN();
		std::string urlImg = jsonMan.getUrl(indexRand);
		_RPT3(0, "Random: %d/%d, Url: %s\n", indexRand,jsonMan.getUrlN(), urlImg.c_str());
		BackgroundImg back = BackFromUrl(urlImg);
		std::string imgPath = std::string("download\\background") + back.extension;
		inetMan.DownloadFile(urlImg, imgPath);
		_RPT1(0, "File downloaded in %s\n", imgPath.c_str());

		

		// build the absolute path of image, because Windows API sucks
		char path[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, path);
		strcat_s(path, MAX_PATH, "\\");
		imgPath = path + imgPath;

		// set new background
		_RPT1(0, "Path: %s\n", imgPath.c_str());
		SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0,(PVOID) imgPath.c_str(), SPIF_UPDATEINIFILE);

		// reset and delete things
		jsonMan.reset();
		delete jsonPage;
		_RPT0(0, "Sleep\n");
		Sleep(interval);
	}

}

bool Timer::Going()
{
	return go;
}

void Timer::InitTimer(Timer* t)
{
	t->Init();
}


