#pragma once
#include "Rendering/Gl.h"
#include "Input/Input.h"
#include "MeshDatabase.h"

namespace Lavender
{
	class Core
	{
		friend class Input;
		friend class MeshDatabase;
	private:
		static Core* instance;
		Gl m_Gl;
		MeshDatabase m_Meshes;

	public:
		Core();

		static Core* GetInstance();

		Gl* GetRenderer();
		Input* GetInput();
	};
}