#include "Core.h"
namespace Lavender
{
	Core* Core::instance = nullptr;

	Core::Core() : m_Gl() 
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
}