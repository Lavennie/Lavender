#pragma once
#include "Object.h"
#include "Information.h"
#include "Idea.h"
#include "LayerIdea.h"

namespace Lavender
{
	class World
	{
	private:
		LayerIdea* m_IdeaLayer;
	public:
		World();
		~World();

		void Update();
		void Render();
		void UpdateSound();
	};
}

