#include "log.h"
#include <iostream>

void Log::Info(const char* message){
	std::cout << message << std::endl;
}

void Log::Warn(const char* message){
	std::cout << message << std::endl;
}

void Log::Error(const char* message){
	std::cout << message << std::endl;
}

