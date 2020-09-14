#include "World.h"

namespace Lavender
{
	World::World() : 
		m_IdeaLayer(std::make_unique<LayerIdea>(10)), 
		m_InfoLayer(std::make_unique<LayerInformation>(10)), 
		m_RealLayer(std::make_unique<LayerReal>())
	{ }

	void World::Update()
	{

	}
	void World::Render()
	{

	}
	void World::UpdateSound()
	{

	}
}