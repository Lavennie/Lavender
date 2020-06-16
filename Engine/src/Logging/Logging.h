#pragma once
#include <string>
#include <time.h>

#define String std::string

namespace Lavender
{
	class Log
	{
	public:
		enum Level : char { LevelError = 0, LevelWarning = 1, LevelInfo = 2, };
	private:
		static time_t m_StartTime;
	public:
		static Level level;
	public:
		Log() = delete;

		static void PrintInfo(const String& msg);
		static void PrintWarning(const String& msg);
		static void PrintError(const String& msg);
	};
}