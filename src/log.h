#pragma once

#include <iostream>
#include "string"
class Log
{
public:
	static void Info(const std::string message)
	{
		std::cout << message << std::endl;
	}
	static void Warn(const std::string message){
		std::cout << message << std::endl;
	}

	static void Error(const std::string message){
		std::cout << message << std::endl;
	}
	static void Debug(const std::string message){
		std::cout << message << std::endl;
	}

private:
	Log() {}
};