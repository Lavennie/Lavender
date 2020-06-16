#pragma once
#include <memory>
#include "Idea.h"

namespace Lavender
{
	class Information
	{
	private:
		std::weak_ptr<Idea> m_Idea;

	public:
		Information() = delete;
		Information(std::shared_ptr<Idea> idea);
	};
}