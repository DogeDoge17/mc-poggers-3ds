#pragma once
#include <time.h>
#include <chrono>
#include <iostream>

using namespace std::chrono;

namespace Time {
	extern uint ticks;	
	extern long int previousTime;
	extern long int currentTime;
	extern long double deltaTime;
	extern bool firstFrame;

	bool SetTime(bool debug = false);
	bool CanUpdate();
};
