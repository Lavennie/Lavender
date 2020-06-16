#include "LayerIdea.h"

namespace Lavender
{
	LayerIdea::LayerIdea(int ideaCount) : m_Ideas(std::vector<Idea>())
	{
		m_Ideas.reserve(ideaCount);
	}
}