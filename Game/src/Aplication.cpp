#define _USE_MATH_DEFINES
#include <cmath>
#include "Rendering/Gl.h"
#include "World.h"
#include <iostream>
#include <memory>
#include <Windows.h>
#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
#include "Rendering/VertexAttribPointer.h"

using namespace Lavender;


int main()
{
	const Color bgColor(0.0f, 0.0f, 0.0f);
	const string filePath = "d:/Projects/Lavender/bin/x64/Debug/";

	Gl gl;
	if (!gl.InitWindow("Lavender"))
	{
		return -1;
	}

	
	// init opengl settings
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	World world;

	Mesh cube;
	cube.InitMesh(filePath + "Models/test.sm");
	Vector3 position(0, 0, 0);

	Idea idea = world.InitIdea();
	idea.AddProperty(Property::Type::Mesh, &cube);
	idea.AddProperty(Property::Type::Position, &position);
	Info info = world.InitInfo(idea);
	Real real = world.InitRealRoot(info);
		
	const string vertexShaderSource =
		"#version 330\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aTexCoord;\n"
		"layout (location = 2) in vec3 aNormal;\n"
		"out vec3 _texCoord;\n"
		"out vec3 _color;\n"
		"uniform mat4 mvp;\n"
		"void main()\n"
		"{\n"
		"	_texCoord = aTexCoord;\n"
		"	_color = (aPos + vec3(1.0, 1.0, 1.0)) / 2.0;\n"
		"   vec4 temp = mvp * vec4(aPos + vec3(10, 0.5, 10), 1.0);\n"
		"   gl_Position = temp;\n"
		"}\0";
	const string fragmentShaderSource =
		"#version 330\n"
		"in vec3 _texCoord;\n"
		"in vec3 _color;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(_color, 1.0);\n"
		"}\0";
	Shader shader;
	shader.InitShader(vertexShaderSource, fragmentShaderSource);
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
			// update
			world.Update(*gl.GetInput());

			// render
			gl.Clear();
			gl.ClearColor(bgColor);
			world.Render();

			shader.Bind();
			Matrix4 mvp = world.GetProjectionMatrix();
			shader.SetUniform("mvp", mvp);
			cube.Draw();

			gl.SwapBuffer();

			// sound
			world.UpdateSound();

			//if (gl.GetInput()->OnKeyDown(VK_SPACE))
			//{
			//	Beep(rand() % 600 + 600, 100);
			//}
			

			// input - needs to be called last to not overwrite onDown & onUp states
			gl.GetInput()->Update();
		}
	}
}