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

	Gl gl;
	if (!gl.InitWindow("Lavender"))
	{
		return -1;
	}
	
	// init opengl settings
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	World world;

	Mesh cube;
	cube.InitMesh("Models/test.sm");
	Matrix4 m;
	//m.Identity();
	m.Scale(0.3f);
		
	const string vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aTexCoord;\n"
		"layout (location = 2) in vec3 aNormal;\n"
		"out vec3 _texCoord;\n"
		"uniform mat4 mvp;\n"
		"void main()\n"
		"{\n"
		"	_texCoord = aTexCoord;\n"
		"   gl_Position = mvp * vec4(aPos, 1.0);\n"
		"}\0";
	const string fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 _texCoord;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
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
			world.Update();

			// render
			gl.Clear();
			gl.ClearColor(bgColor);
			world.Render();

			shader.Bind();
			shader.SetUniform("mvp", m);
			cube.Draw();

			gl.SwapBuffer();

			// sound
			world.UpdateSound();

			if (gl.GetInput()->OnKeyDown(VK_SPACE))
			{
				Beep(rand() % 600 + 600, 100);
			}

			// input - needs to be called last to not overwrite onDown & onUp states
			gl.GetInput()->Update();
		}
	}
}