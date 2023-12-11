#pragma once
#include <iostream>
#include <cstdio>
#include <string>

double clamp(double value, double min, double max)
{	
	if(value >= min && value <= max){
		//printf("value %f was within range of %f and %f\n", value,min,max);
		return value;
	}
	else if(value <= min){
		//printf("value %f was clamped to the min %f\n", value,min);
		value = min;
		return min;
	}
	else if(value >= max){
		//printf("value %f was clamped to the max %f\n", value,max);
		value = max;
		return max;
	}

	printf("uhh it um idk");
	return value;
}

void printfile(const char* path)
{
	FILE* f = fopen(path, "r");
	if (f)
	{
		char mystring[100];
		while (fgets(mystring, sizeof(mystring), f))
		{
			int a = strlen(mystring);
			if (mystring[a-1] == '\n')
			{
				mystring[a-1] = 0;
				if (mystring[a-2] == '\r')
					mystring[a-2] = 0;
			}
			puts(mystring);
		}
		printf(">>EOF<<\n");
		fclose(f);
	}
}

const std::string vformat(const char * const zcFormat, ...)
{

// initialize use of the variable argument array
	va_list vaArgs;
	va_start(vaArgs, zcFormat);

// reliably acquire the size
// from a copy of the variable argument array
// and a functionally reliable call to mock the formatting
	va_list vaArgsCopy;
	va_copy(vaArgsCopy, vaArgs);
	const int iLen = std::vsnprintf(NULL, 0, zcFormat, vaArgsCopy);
	va_end(vaArgsCopy);

// return a formatted string without risking memory mismanagement
// and without assuming any compiler or platform specific behavior
	std::vector<char> zc(iLen + 1);
	std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
	va_end(vaArgs);
	return std::string(zc.data(), iLen);
}

//I give 'em the yukari stare when there is no built-in way to find an array length
template <typename T, std::size_t N>
std::size_t length(T(&)[N])
{
    return N;
}

//Makes a number positive btw i know abs is a thing but like uh erm kys???
double positive(double numb)
{
	if(numb > 0) return numb;
	else return -numb;
}

double negative(double numb)
{
	if(numb < 0) return numb;
	else return -numb;
}