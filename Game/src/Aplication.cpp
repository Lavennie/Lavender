#include "Rendering/Gl.h"
#include <iostream>
#include <memory>
#include <Tests\TestingEnv.h>

using namespace Lavender;


int main()
{
	Gl gl;
	if (!gl.InitWindow("Lavender"))
	{
		return -1;
	}

	// create and run tests
	// TestingEnv::TestingEnv();
	// .

	MSG msg;
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// update, draw, ...
	}
}