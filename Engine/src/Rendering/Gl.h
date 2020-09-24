#pragma once
#include <windows.h>
#include <memory>
#include "Math/Color.h"
#include "Input/Input.h"

namespace Lavender
{
	class Gl
	{
	private:
		HWND m_Hwnd;
		HDC m_Hdc;
		HGLRC m_Hrc;
		bool m_HasWindow;
		std::unique_ptr<Input> m_Input;
	public:
		Gl();
		~Gl();

		bool InitWindow(const char* title);

		bool HasWindow() const;

		void Clear() const;
		void ClearColor(const Color& color) const;
		void SwapBuffer() const;

		Input* GetInput() const;
	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}