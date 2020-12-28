#pragma once
#include "Rendering/Gl.h"
#include "Input/Input.h"

namespace Lavender
{
	class Core
	{
		friend class Input;
	private:
		Gl m_Gl;
		static Core* instance;

	public:
		Core();

		static Core* GetInstance();

		Gl* GetRenderer();
		Input* GetInput();
	};
}