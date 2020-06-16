#pragma once
#include <vector>
#include "Idea.h"

namespace Lavender
{
	class LayerIdea
	{
	private:
		std::vector<Idea> m_Ideas;
	public:
		LayerIdea(int ideaCount);
	};
}