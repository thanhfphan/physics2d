#pragma once

class Log
{
public:
	static void Info(const char *message);
	static void Warn(const char *message);
	static void Error(const char *message);
private:
	Log() {}
};