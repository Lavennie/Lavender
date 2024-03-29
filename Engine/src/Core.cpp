#include "Core.h"
namespace Lavender
{
	Core* Core::instance = nullptr;

	Core::Core() : m_Gl(), m_Meshes(), m_Shaders(), m_Collisions()
	{
		instance = this;
	}

	Core* Core::GetInstance()
	{
		return Core::instance;
	}

	Gl* Core::GetRenderer()
	{
		return &m_Gl;
	}
	Input* Core::GetInput()
	{
		return m_Gl.GetInput();
	}
	ShaderDatabase& Core::GetShaders()
	{
		return m_Shaders;
	}
	CollisionList& Core::GetCollisions()
	{
		return m_Collisions;
	}
}