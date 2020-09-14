#pragma once
#include <windows.h>
#include "Math/Color.h"

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

		void Clear() const;
		void ClearColor(const Color& color) const;
		void SwapBuffer() const;
	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}