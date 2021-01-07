#include "Logging.h"
#include <iostream>

namespace Lavender
{
	Log::Level Log::level = Log::Level::LevelInfo;
	time_t Log::m_StartTime = time(0);

	void Log::Print(const char* msg, Level level)
	{
		if (level > Log::level) { return; }
		switch (level)
		{
		case Lavender::Log::Level::LevelError:
			std::cout << "\033[91m" << "[" << difftime(time(0), m_StartTime) << "] " << msg << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelWarning:
			std::cout << "\033[93m" << "[" << difftime(time(0), m_StartTime) << "] " << msg << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelInfo:
			std::cout << "[" << difftime(time(0), m_StartTime) << "] " << msg << std::endl;
			break;
		}
	}
	void Log::Print(const String& msg, Level level)
	{
		if (level > Log::level) { return; }
		switch (level)
		{
		case Lavender::Log::Level::LevelError:
			std::cout << "\033[91m" << "[" << difftime(time(0), m_StartTime) << "] " << msg << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelWarning:
			std::cout << "\033[93m" << "[" << difftime(time(0), m_StartTime) << "] " << msg << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelInfo:
			std::cout << "[" << difftime(time(0), m_StartTime) << "] " << msg << std::endl;
			break;
		}
	}
	void Log::Print(const Vector2& msg, Level level)
	{
		if (level > Log::level) { return; }
		switch (level)
		{
		case Lavender::Log::Level::LevelError:
			std::cout << "\033[91m" << "[" << difftime(time(0), m_StartTime) << "] " << msg.x << ", " << msg.y << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelWarning:
			std::cout << "\033[93m" << "[" << difftime(time(0), m_StartTime) << "] " << msg.x << ", " << msg.y << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelInfo:
			std::cout << "[" << difftime(time(0), m_StartTime) << "] " << msg.x << ", " << msg.y << std::endl;
			break;
		}
	}
	void Log::Print(const Vector3& msg, Level level)
	{
		if (level > Log::level) { return; }
		switch (level)
		{
		case Lavender::Log::Level::LevelError:
			std::cout << "\033[91m" << "[" << difftime(time(0), m_StartTime) << "] " << msg.x << ", " << msg.y << ", " << msg.z << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelWarning:
			std::cout << "\033[93m" << "[" << difftime(time(0), m_StartTime) << "] " << msg.x << ", " << msg.y << ", " << msg.z << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelInfo:
			std::cout << "[" << difftime(time(0), m_StartTime) << "] " << msg.x << ", " << msg.y << ", " << msg.z << std::endl;
			break;
		}
	}
	void Log::Print(const Quaternion& msg, Level level)
	{
		if (level > Log::level) { return; }
		switch (level)
		{
		case Lavender::Log::Level::LevelError:
			std::cout << "\033[91m" << "[" << difftime(time(0), m_StartTime) << "] " << msg.v.x << ", " << msg.v.y << ", " << msg.v.z << ", " << msg.w << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelWarning:
			std::cout << "\033[93m" << "[" << difftime(time(0), m_StartTime) << "] " << msg.v.x << ", " << msg.v.y << ", " << msg.v.z << ", " << msg.w << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelInfo:
			std::cout << "[" << difftime(time(0), m_StartTime) << "] " << msg.v.x << ", " << msg.v.y << ", " << msg.v.z << ", " << msg.w << std::endl;
			break;
		}
	}
	void Log::Print(const Color& msg, Level level)
	{
		if (level > Log::level) { return; }
		switch (level)
		{
		case Lavender::Log::Level::LevelError:
			std::cout << "\033[91m" << "[" << difftime(time(0), m_StartTime) << "] " << msg.r << ", " << msg.g << ", " << msg.b << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelWarning:
			std::cout << "\033[93m" << "[" << difftime(time(0), m_StartTime) << "] " << msg.r << ", " << msg.g << ", " << msg.b << "\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelInfo:
			std::cout << "[" << difftime(time(0), m_StartTime) << "] " << msg.r << ", " << msg.g << ", " << msg.b << std::endl;
			break;
		}
	}
	void Log::Print(const Matrix4& msg, Level level)
	{
		if (level > Log::level) { return; }
		switch (level)
		{
		case Lavender::Log::Level::LevelError:
			std::cout << "\033[91m" << "[" << difftime(time(0), m_StartTime) << "] " << 
				"| " << msg[0] << ", " << msg[4] << ", " << msg[8]  << ", " << msg[12] << " |" <<
				"| " << msg[1] << ", " << msg[5] << ", " << msg[9]  << ", " << msg[13] << " |" <<
				"| " << msg[2] << ", " << msg[6] << ", " << msg[10] << ", " << msg[14] << " |" <<
				"| " << msg[3] << ", " << msg[7] << ", " << msg[11] << ", " << msg[15] << " |" <<
				"\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelWarning:
			std::cout << "\033[93m" << "[" << difftime(time(0), m_StartTime) << "] " <<
				"| " << msg[0] << ", " << msg[4] << ", " << msg[8] << ", " << msg[12] << " |" <<
				"| " << msg[1] << ", " << msg[5] << ", " << msg[9] << ", " << msg[13] << " |" <<
				"| " << msg[2] << ", " << msg[6] << ", " << msg[10] << ", " << msg[14] << " |" <<
				"| " << msg[3] << ", " << msg[7] << ", " << msg[11] << ", " << msg[15] << " |" <<
				"\033[0m" << std::endl;
			break;
		case Lavender::Log::Level::LevelInfo:
			std::cout << "[" << difftime(time(0), m_StartTime) << "] " <<
				"| " << msg[0] << ", " << msg[4] << ", " << msg[8] << ", " << msg[12] << " |" <<
				"| " << msg[1] << ", " << msg[5] << ", " << msg[9] << ", " << msg[13] << " |" <<
				"| " << msg[2] << ", " << msg[6] << ", " << msg[10] << ", " << msg[14] << " |" <<
				"| " << msg[3] << ", " << msg[7] << ", " << msg[11] << ", " << msg[15] << " |" <<
				std::endl;
			break;
		}
	}
}