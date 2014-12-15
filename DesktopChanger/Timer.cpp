#include "Timer.h"
#include <iostream>
#include <Windows.h>
#include "Background.h"


Timer::Timer(int i)
{
	interval = i*1000;
	go = true;
	_thread = new std::thread(InitTimer,*this);
}

Timer::Timer() : Timer::Timer(1)
{ }


Timer::~Timer()
{
	
}

bool Timer::Start()
{
	_thread->detach();
	return true;
}

void Timer::Stop()
{
	go = false;
}

void Timer::Init()
{
#ifndef _DEBUG
	while (go)
#endif
	{
		std::cout << "refresh" << std::endl;
		// TODO: download image
		
		/* set background (background.jpg/png) */
		
		Background back = Background("sfondo", ".jpg");

		// build the path of image
		char path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,path);
		lstrcat(path, "\\");
		lstrcat(path, back.name.c_str());
		lstrcat(path, back.extension.c_str());

		if (_DEBUG) std::cout << path << std::endl;

		// set new background
		SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, path, SPIF_UPDATEINIFILE);
		
		Sleep(interval);
	}

}

bool Timer::Going()
{
	return go;
}

void InitTimer(Timer t)
{
	t.Init();
}