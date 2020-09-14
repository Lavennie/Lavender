#pragma once
#include <memory>
#include "Object.h"
#include "Information.h"
#include "Idea.h"
#include "LayerIdea.h"
#include "LayerInformation.h"
#include "LayerReal.h"

namespace Lavender
{
	class World
	{
	private:
		std::unique_ptr<LayerIdea> m_IdeaLayer;
		std::unique_ptr<LayerInformation> m_InfoLayer;
		std::unique_ptr<LayerReal> m_RealLayer;
	public:
		World();

		void Update();
		void Render();
		void UpdateSound();
	};
}

