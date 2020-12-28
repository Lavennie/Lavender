#include "Input.h"
#include "Core.h"
#include "Logging/Logging.h"
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

	void Input::Init(bool visible)
	{
		Vector2 center = Core::GetInstance()->m_Gl.GetInScreenCenter();
		SetCursorPos(center.x, center.y);
		ShowCursor(visible);
	}
	void Input::UpdateKeys()
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
	void Input::UpdateMouse()
	{
		Vector2 center = Core::GetInstance()->m_Gl.GetInScreenCenter();

		m_DeltaMousePos = ScreenMousePosition() - center;
		m_DeltaMousePos.y = -m_DeltaMousePos.y;
		SetCursorPos(center.x, center.y);
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

	bool Input::KeyDown(unsigned int virtualKey)
	{
		return Core::GetInstance()->m_Gl.GetInput()->m_KeyStates[virtualKey] == KEY_DOWN || Core::GetInstance()->m_Gl.GetInput()->m_KeyStates[virtualKey] == KEY_ON_DOWN;
	}
	bool Input::KeyUp(unsigned int virtualKey)
	{
		return Core::GetInstance()->m_Gl.GetInput()->m_KeyStates[virtualKey] == KEY_UP || Core::GetInstance()->m_Gl.GetInput()->m_KeyStates[virtualKey] == KEY_ON_UP;
	}
	bool Input::OnKeyDown(unsigned int virtualKey)
	{
		return Core::GetInstance()->m_Gl.GetInput()->m_KeyStates[virtualKey] == KEY_ON_DOWN;
	}
	bool Input::OnKeyUp(unsigned int virtualKey)
	{
		return Core::GetInstance()->m_Gl.GetInput()->m_KeyStates[virtualKey] == KEY_ON_UP;
	}
	Vector2 Input::MousePosition()
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(Core::GetInstance()->m_Gl.m_Hwnd, &p);
		return Vector2(p.x, p.y);
	}
	Vector2 Input::ScreenMousePosition()
	{
		POINT p;
		GetCursorPos(&p);
		return Vector2(p.x, p.y);
	}
	Vector2 Input::DeltaMousePosition()
	{
		return Core::GetInstance()->m_Gl.GetInput()->m_DeltaMousePos;
	}
}