#pragma once
#include <memory>
#include "Idea.h"
#include "SubIdea.h"

namespace Lavender
{
	class Info : public SubIdea
	{
	public:
		Info(const Idea* idea);

		void Adjust();
	};
}