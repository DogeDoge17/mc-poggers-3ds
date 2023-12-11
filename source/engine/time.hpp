#pragma once
//#include "main.h"
#include <time.h>
#include <chrono>
#include <iostream>

using namespace std::chrono;

namespace Time {

	uint ticks;	

	long int previousTime;
	long int currentTime;
	long double deltaTime;
	bool firstFrame = true;

	bool SetTime(bool debug = false)
	{

		ticks++;

		struct timeval tp;
		gettimeofday(&tp, NULL);
		currentTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;

		if(!firstFrame){
			deltaTime = currentTime -previousTime;
			deltaTime /= 1000;

		}

		previousTime = currentTime;

		//prevents the deltaTime from absolutely destroying game functions
		if(deltaTime > 100 || deltaTime < 0)
			return false;

		firstFrame = false;
		if(!debug)
			return true;

		std::cout << "deltaTime "<<deltaTime << "\n";
		std::cout <<"ticks "<< ticks << "\n";
		std::cout << "\n";
		std::cout <<"previousTime "<< previousTime << "\n";
		std::cout <<"currentTime "<< currentTime << std::endl;
		return true;
	}
	bool CanUpdate()
	{
		return false;
	}	
};

