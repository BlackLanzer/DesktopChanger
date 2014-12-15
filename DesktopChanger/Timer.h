#include <thread>

#pragma once



class Timer
{
	std::thread* _thread;
	int interval;
	bool go;

public:
	Timer();
	Timer(int interval);
	~Timer();
	bool Start();
	void Stop();
	bool Going();
	void Init();
};

// function called by the new thread
void InitTimer(Timer t);
