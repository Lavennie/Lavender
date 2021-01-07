#pragma once
#include "Idea.h"

namespace Lavender
{
	class SubIdea : public Idea
	{

	private:
		const Idea* m_Idea;

	public:
		SubIdea(const Idea* idea);
		const Property* GetProperty(Property::Type type) const override;

		const Idea* GetIdea() const;
	};
}