#include <thread>

#pragma once

class Timer
{
	std::thread* _thread;
	int interval;
	bool go;
	// function called by the new thread
	static void InitTimer(Timer t);

public:
	Timer();
	Timer(int interval);
	~Timer();
	bool Start();
	void Stop();
	bool Going();
	void Init();

};


