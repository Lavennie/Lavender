#include "Rendering/Gl.h"

using namespace Lavender;

int main()
{
	Gl gl;
	if (!gl.InitWindow("Lavender"))
	{
		return -1;
	}

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