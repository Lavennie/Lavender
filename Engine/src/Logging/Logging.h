#pragma once
#include <string>
#include <time.h>
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/Color.h"
#include "Math/Matrix4.h"

#define String std::string

namespace Lavender
{
	class Log
	{
	public:
		enum class Level { LevelError = 0, LevelWarning = 1, LevelInfo = 2, };
	private:
		static time_t m_StartTime;
	public:
		static Level level;

	public:
		Log() = delete;
		static void Print(const char* msg, Level level = Level::LevelInfo);
		static void Print(const String& msg, Level level = Level::LevelInfo);
		static void Print(const Vector2& msg, Level level = Level::LevelInfo);
		static void Print(const Vector3& msg, Level level = Level::LevelInfo);
		static void Print(const Quaternion& msg, Level level = Level::LevelInfo);
		static void Print(const Color& msg, Level level = Level::LevelInfo);
		static void Print(const Matrix4& msg, Level level = Level::LevelInfo);
	};
}