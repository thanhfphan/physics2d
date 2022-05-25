#pragma once

#include <iostream>
class Log
{
public:
	static void Info(const char *message)
	{
		std::cout << message << std::endl;
	}
	static void Warn(const char *message){
		std::cout << message << std::endl;
	}

	static void Error(const char *message){
		std::cout << message << std::endl;
	}

private:
	Log() {}
};