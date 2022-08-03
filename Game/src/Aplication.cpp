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
#include "Collision/Collision.h"

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

	World world(70, monitorSize, 0.1f, 100);

		Mesh* cube = MeshDatabase::LoadMesh(filePath + "Models/test.sm", false);
		Shader* shader = ShaderDatabase::LoadShader(filePath + "Shaders/vertex.vs", filePath + "Shaders/fragment.fs");

		Idea& floorIdea = world.InitIdea(Vector3(0, -3, 0), Quaternion(), Vector3(10, 0.1f, 10));
		floorIdea.AddProperty<PropertyModel, PropertyModel>(Property::Type::Mesh, cube);
		floorIdea.AddProperty<PropertyShading, PropertyShading>(Property::Type::Shader, shader);
		Info& floorInfo = world.InitInfo(floorIdea);
		Real& floorReal = world.InitRealRoot(floorInfo);

		Idea& cubeIdea = world.InitIdea(Vector3(0, 0, 3), Quaternion(45, 45, 45));
		cubeIdea.AddProperty<PropertyModel, PropertyModel>(Property::Type::Mesh, cube);
		cubeIdea.AddProperty<PropertyShading, PropertyShading>(Property::Type::Shader, shader);
		Info& cubeInfo = world.InitInfo(cubeIdea);
		Real& cubeReal = world.InitRealRoot(cubeInfo);
		cubeReal.AddCollider(Vector3(0, 0, 0), 1.0f);


	Idea& playerIdea = world.InitIdea();
	Info& playerInfo = world.InitInfo(playerIdea);
	Real& playerReal = world.InitRealRoot(playerInfo);
	playerReal.AddCollider(Vector3(0, 0, 0));
		
	// main loop
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
			// mouse input
			gl->GetInput()->UpdateMouse();

			// colliders
			world.UpdateColliders();

			// update
			world.Update();
			playerIdea.SetPosition(world.GetCamera()->position);

			// render
			gl->Clear();
			gl->ClearColor(bgColor);

			world.Render();

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
	cout << endl << endl;
}