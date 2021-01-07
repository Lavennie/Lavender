#include "Gl.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <windowsx.h>
#include "Logging/Logging.h"

namespace Lavender
{
	Gl::Gl() : m_Hwnd(NULL), m_Hdc(NULL), m_Hrc(NULL), m_HasWindow(false), m_Input(std::make_unique<Input>()) { }
	Gl::~Gl()
	{
		wglMakeCurrent(NULL, NULL);
		RemoveProp(m_Hwnd, (LPCWSTR)L"MyWindow");
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
		Log::Print("Deleted opengl context and window");
	}

	bool Gl::InitWindow(const char* title, Vector2 windowSize)
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
			WS_POPUP | WS_VISIBLE,
			0, 0, windowSize.x, windowSize.y,
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
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
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

		SetProp(m_Hwnd, (LPCWSTR)L"MyWindow", (HANDLE)this);

		m_HasWindow = true;

		return true;
	}

	bool Gl::HasWindow() const
	{
		return m_HasWindow;
	}
	Vector2 Gl::GetClientSize() const
	{
		RECT r;
		GetClientRect(m_Hwnd, &r);
		return Vector2(r.right, r.bottom);
	}
	Vector2 Gl::GetInScreenCenter() const
	{
		RECT r;
		GetClientRect(m_Hwnd, &r);
		POINT p;
		p.x = r.right / 2.0f;
		p.y = r.bottom / 2.0f;
		ClientToScreen(m_Hwnd, &p);
		return Vector2(p.x, p.y);
	}

	void Gl::Close() const
	{
		PostMessage(m_Hwnd, WM_CLOSE, 0, 0);
	}

	void Gl::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
	}
	void Gl::ClearColor(const Color& color) const
	{
		glClearColor(color.r, color.g, color.b, 1.0f);
	}
	void Gl::SwapBuffer() const
	{
		SwapBuffers(m_Hdc);
	}

	Input* Gl::GetInput() const
	{
		return m_Input.get();
	}

	LRESULT CALLBACK Gl::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_KEYDOWN:
		{
			Gl* window = (Gl*)GetProp(hwnd, (LPCWSTR)L"MyWindow");
			if (window != nullptr)
			{
				window->m_Input->RegisterKeyDown(wParam);
			}
			return 0;
		}
		case WM_KEYUP:
		{
			Gl* window = (Gl*)GetProp(hwnd, (LPCWSTR)L"MyWindow");
			if (window != nullptr)
			{
				window->m_Input->RegisterKeyUp(wParam);
			}
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
}
