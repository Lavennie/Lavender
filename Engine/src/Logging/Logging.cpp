#include "Logging.h"
#include <iostream>

namespace Lavender
{
	Log::Level Log::level = Log::LevelInfo;
	time_t Log::m_StartTime = time(0);

	void Log::PrintInfo(const String& msg)
	{
		if (Log::level >= LevelInfo)
		{
			std::cout << "[" << difftime(time(0), m_StartTime) << "] " << msg << std::endl;
		}
	}
	void Log::PrintInfo(const char* msg)
	{
		if (Log::level >= LevelInfo)
		{
			std::cout << "[" << difftime(time(0), m_StartTime) << "] " << msg << std::endl;
		}
	}
	void Log::PrintWarning(const String& msg)
	{
		if (Log::level >= LevelWarning)
		{
			std::cout << "\033[93m" << "[" << difftime(time(0), m_StartTime) << "] " << msg << "\033[0m" << std::endl;
		}
	}
	void Log::PrintWarning(const char* msg)
	{
		if (Log::level >= LevelWarning)
		{
			std::cout << "\033[93m" << "[" << difftime(time(0), m_StartTime) << "] " << msg << "\033[0m" << std::endl;
		}
	}
	void Log::PrintError(const String& msg)
	{
		if (Log::level >= LevelError)
		{
			std::cout << "\033[91m" << "[" << difftime(time(0), m_StartTime) << "] " << msg << "\033[0m" << std::endl;
		}
	}
	void Log::PrintError(const char* msg)
	{
		if (Log::level >= LevelError)
		{
			std::cout << "\033[91m" << "[" << difftime(time(0), m_StartTime) << "] " << msg << "\033[0m" << std::endl;
		}
	}
}