#pragma once
#include <memory>
#include "Object.h"
#include "Information.h"
#include "Idea.h"
#include "LayerIdea.h"

namespace Lavender
{
	class World
	{
	private:
		std::shared_ptr<LayerIdea> m_IdeaLayer;
	public:
		World(std::shared_ptr<LayerIdea> ideaLayer);

		void Update();
		void Render();
		void UpdateSound();
	};
}

