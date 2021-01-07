#pragma once
#include "Rendering/Gl.h"
#include "Input/Input.h"
#include "MeshDatabase.h"
#include "ShaderDatabase.h"
#include "Collision/CollisionList.h"

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
		ShaderDatabase m_Shaders;
		CollisionList m_Collisions;

	public:
		Core();

		static Core* GetInstance();

		Gl* GetRenderer();
		Input* GetInput();
		ShaderDatabase& GetShaders();
		CollisionList& GetCollisions();
	};
}