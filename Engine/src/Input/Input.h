#pragma once
#define KEY_DOWN 0
#define KEY_ON_DOWN 1
#define KEY_UP 2
#define KEY_ON_UP 3
#include "Math/Vector2.h"

namespace Lavender
{
	constexpr size_t KEY_COUNT = 254;
	class Input
	{
	private:
		Vector2 m_DeltaMousePos;
		char m_KeyStates[KEY_COUNT]; // 0 = up, 1 = down this frame, 2 = down, 3 = up this frame
	public:

		Input();
		~Input();

		void Init(bool visible);
		void UpdateKeys();
		void UpdateMouse();

		void RegisterKeyDown(unsigned int virtualKey);
		void RegisterKeyUp(unsigned int virtualKey);

		static bool KeyDown(unsigned int virtualKey);
		static bool KeyUp(unsigned int virtualKey);
		static bool OnKeyDown(unsigned int virtualKey);
		static bool OnKeyUp(unsigned int virtualKey);
		static Vector2 MousePosition();
		static Vector2 ScreenMousePosition();
		static Vector2 DeltaMousePosition();
	};
}