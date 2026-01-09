#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdarg>

double clamp(double value, double min, double max);
void printfile(const char* path);
const std::string vformat(const char * const zcFormat, ...);

template <typename T, std::size_t N>
std::size_t length(T(&)[N])
{
    return N;
}

double positive(double numb);
double negative(double numb);
