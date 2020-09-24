#include "Input.h"
#include "Logging/logging.h"
#include <iostream>

namespace Lavender
{
	Input::Input()
	{
		for (int i = 0; i < KEY_COUNT; ++i)
		{
			m_KeyStates[i] = KEY_UP;
		}
	}
	Input::~Input()
	{
		Log::PrintInfo("Deleted input");
	}

	void Input::Update()
	{
		for (int i = 0; i < KEY_COUNT; ++i)
		{
			if (m_KeyStates[i] == KEY_ON_DOWN)
			{
				m_KeyStates[i] = KEY_DOWN;
			}
			else if (m_KeyStates[i] == KEY_ON_UP)
			{
				m_KeyStates[i] = KEY_UP;
			}
		}
	}

	void Input::RegisterKeyDown(unsigned int virtualKey)
	{
		if (m_KeyStates[virtualKey] != KEY_DOWN)
		{
			m_KeyStates[virtualKey] = KEY_ON_DOWN;
		}
	}
	void Input::RegisterKeyUp(unsigned int virtualKey)
	{
		if (m_KeyStates[virtualKey] != KEY_UP)
		{
			m_KeyStates[virtualKey] = KEY_ON_UP;
		}
	}

	bool Input::KeyDown(unsigned int virtualKey) const
	{
		return m_KeyStates[virtualKey] == KEY_DOWN || m_KeyStates[virtualKey] == KEY_ON_DOWN;
	}
	bool Input::KeyUp(unsigned int virtualKey) const
	{
		return m_KeyStates[virtualKey] == KEY_UP || m_KeyStates[virtualKey] == KEY_ON_UP;
	}
	bool Input::OnKeyDown(unsigned int virtualKey) const
	{
		return m_KeyStates[virtualKey] == KEY_ON_DOWN;
	}
	bool Input::OnKeyUp(unsigned int virtualKey) const
	{
		return m_KeyStates[virtualKey] == KEY_ON_UP;
	}
}