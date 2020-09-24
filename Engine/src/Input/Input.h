#pragma once
namespace Lavender
{
	constexpr size_t KEY_COUNT = 254;
	class Input
	{
	private:
		char m_KeyStates[KEY_COUNT]; // 0 = up, 1 = down this frame, 2 = down, 3 = up this frame
	public:
		const char KEY_DOWN = 0;
		const char KEY_ON_DOWN = 1;
		const char KEY_UP = 2;
		const char KEY_ON_UP = 3;

		Input();
		~Input();

		void Update();

		void RegisterKeyDown(unsigned int virtualKey);
		void RegisterKeyUp(unsigned int virtualKey);

		bool KeyDown(unsigned int virtualKey) const;
		bool KeyUp(unsigned int virtualKey) const;
		bool OnKeyDown(unsigned int virtualKey) const;
		bool OnKeyUp(unsigned int virtualKey) const;
	};
}