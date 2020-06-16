#include "World.h"

namespace Lavender
{
	World::World() : m_Physical(new Dimension<Object>), m_Information(new Dimension<Information>), m_Idea(new Dimension<Idea>)
	{

	}
	World::~World()
	{
		delete m_Physical;
		delete m_Information;
		delete m_Idea;
	}

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