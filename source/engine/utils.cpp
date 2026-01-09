#include "engine/utils.hpp"
#include <cstring>

double clamp(double value, double min, double max)
{	
	if(value >= min && value <= max){
		return value;
	}
	else if(value <= min){
		value = min;
		return min;
	}
	else if(value >= max){
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
	va_list vaArgs;
	va_start(vaArgs, zcFormat);

	va_list vaArgsCopy;
	va_copy(vaArgsCopy, vaArgs);
	const int iLen = std::vsnprintf(NULL, 0, zcFormat, vaArgsCopy);
	va_end(vaArgsCopy);

	std::vector<char> zc(iLen + 1);
	std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
	va_end(vaArgs);
	return std::string(zc.data(), iLen);
}

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
