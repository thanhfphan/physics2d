#pragma once

#include <iostream>
#include "string"
#include <sstream>
#include <iomanip>

namespace TK
{
	class Log
	{
	private:
		static std::string get_time()
		{
			auto t = std::time(nullptr);
			auto tm = *std::localtime(&t);

			std::ostringstream oss;
			oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
			auto str = oss.str();
			return str;
		}

		static std::string make_green()
		{
			return "\033[1;32m";
		}

		static std::string make_red()
		{
			return "\033[1;31m";
		}

		static std::string make_cyan()
		{
			return "\033[1;36m";
		}

		static std::string make_magenta()
		{
			return "\033[1;35m";
		}

		static std::string reset_color()
		{
			return "\033[0m";
		}

	public:
		static void Info(const std::string message)
		{
			std::cout << get_time() << make_green() << " [INFO]: " << reset_color() << message << std::endl;
		}

		static void Warn(const std::string message)
		{
			std::cout << get_time() << make_cyan() << " [WARN]: " << reset_color() << message << std::endl;
		}

		static void Error(const std::string message)
		{
			std::cout << get_time() << make_red() << " [ERROR]: " << reset_color() << message << std::endl;
		}

		static void Debug(const std::string message)
		{
			std::cout << get_time() << make_magenta() << " [DEBUG]: " << reset_color() << message << std::endl;
		}

	private:
		Log() {}
	};
}

using TK::Log;