#define _USE_MATH_DEFINES
#include <cmath>
#include "Rendering/Gl.h"
#include "World.h"
#include <iostream>
#include <memory>
#include <Windows.h>
#include "Core.h"
#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
#include "Rendering/VertexAttribPointer.h"

using namespace Lavender;


int main()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, -1000, 100, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	const Color bgColor(0.0f, 0.0f, 0.0f);
	const string filePath = "d:/Projects/Lavender/bin/x64/Debug/";

	HMONITOR monitor = MonitorFromPoint({ 0, 0 }, MONITOR_DEFAULTTOPRIMARY);
	MONITORINFO monitorInfo;
	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &monitorInfo);
	Vector2 monitorSize = Vector2(monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top);

	std::cout << "Window size: " << monitorSize.x << "x" << monitorSize.y << std::endl;
	Core core;
	Gl* gl = core.GetRenderer();
	if (!gl->InitWindow("Lavender", monitorSize))
	{
		return -1;
	}
	gl->GetInput()->Init(false);
	
	// init opengl settings
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	World world(70, monitorSize, 0.1f, 20);

	Mesh cube;
	cube.InitMesh(filePath + "Models/test.sm");
	Vector3 position(0, 0, 0);

	Idea idea = world.InitIdea();
	idea.AddProperty(Property::Type::Mesh, &cube);
	idea.AddProperty(Property::Type::Position, &position);
	Info info = world.InitInfo(idea);
	Real real = world.InitRealRoot(info);
		
	Shader shader;
	shader.InitShaderFromFile(filePath + "Shaders/vertex.vs", filePath + "Shaders/fragment.fs");
	shader.Bind();

	MSG msg;
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			gl->GetInput()->UpdateMouse();

			// update
			world.Update();

			// render
			gl->Clear();
			gl->ClearColor(bgColor);
			world.Render();

			shader.Bind();
			Matrix4 mvp = world.GetProjectionMatrix();
			shader.SetUniform("mvp", mvp);
			cube.Draw();

			gl->SwapBuffer();

			// sound
			world.UpdateSound();


			if (Input::OnKeyDown(VK_ESCAPE))
			{
				gl->Close();
			}
			//if (Input::KeyDown(VK_SPACE))
			//{
			//	Beep(rand() % 600 + 600, 100);
			//}
			

			// input - needs to be called last to not overwrite onDown & onUp states
			gl->GetInput()->UpdateKeys();
		}
	}
}