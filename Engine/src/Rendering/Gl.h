#pragma once
#include <windows.h>

namespace Lavender
{
	class Gl
	{
	private:
		HWND m_Hwnd;
		HDC m_Hdc;
		HGLRC m_Hrc;
		bool m_HasWindow;
	public:
		Gl();
		~Gl();

		bool InitWindow(const char* title);

		bool HasWindow() const;
	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}