#include "Gl.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "Log/Log.h"
#include <iostream>

namespace Lavender
{
	Gl::Gl() : m_Hwnd(NULL), m_Hdc(NULL), m_Hrc(NULL), m_HasWindow(false) { }
	Gl::~Gl()
	{
		wglMakeCurrent(NULL, NULL);
		if (m_Hdc != NULL)
		{
			ReleaseDC(m_Hwnd, m_Hdc);
		}
		if (m_Hrc != NULL)
		{
			wglDeleteContext(m_Hrc);
		}
		if (m_Hwnd != NULL)
		{
			DestroyWindow(m_Hwnd);
		}
	}

	bool Gl::InitWindow(const char* title)
	{
		static HINSTANCE hInstance = NULL;

		// register window only the first time
		if (!hInstance)
		{
			hInstance = GetModuleHandle(NULL);
			WNDCLASSEX wcex;
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
			wcex.lpfnWndProc = WindowProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = hInstance; 
			wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName = NULL;
			wcex.lpszClassName = TEXT("OpenGL");
			wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			if (!RegisterClassEx(&wcex))
			{
				return false;
			}
		}


		m_Hwnd = CreateWindowEx(NULL, TEXT("OpenGL"), TEXT("Lavender"),
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, NULL, hInstance, NULL);

		if (m_Hwnd == NULL)
		{
			return false;
		}

		m_Hdc = GetDC(m_Hwnd);

		// there is no guarantee that the contents of the stack that become
		// the pfd are zeroed, therefore make sure to clear these bits
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;

		int pf = ChoosePixelFormat(m_Hdc, &pfd);
		if (pf == 0)
		{
			return false;
		}
		if (SetPixelFormat(m_Hdc, pf, &pfd) == FALSE)
		{
			return false;
		}

		DescribePixelFormat(m_Hdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

		m_Hrc = wglCreateContext(m_Hdc);
		wglMakeCurrent(m_Hdc, m_Hrc);

		ShowWindow(m_Hwnd, SW_SHOWNORMAL);

		m_HasWindow = true;
		return true;
	}

	bool Gl::HasWindow() const
	{
		return m_HasWindow;
	}

	LRESULT CALLBACK Gl::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
		default:
			break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
