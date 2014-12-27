#include <thread>
#include "InternetManager.h"
#include "JsonManager.h"

#pragma once

class Timer
{
	std::thread* _thread;
	char exePath[MAX_PATH];
	int interval;
	bool go;
	InternetManager inetMan;
	JsonManager jsonMan;
	// function called by the new thread
	static void InitTimer(Timer* t);

public:
	Timer();
	Timer(int interval);
	~Timer();
	bool Start();
	void Stop();
	bool Going();
	void Init();

};


