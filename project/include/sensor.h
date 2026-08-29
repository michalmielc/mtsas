#pragma once
#include<string>

struct  Sensor 
{
	int id;
	std::string name;
	std::string unit;
	double a,b;
	double min, max;
};
