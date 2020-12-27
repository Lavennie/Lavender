#include "SubIdea.h"

namespace Lavender
{
	SubIdea::SubIdea(const Idea* idea) : Idea(), m_Idea(idea) { }

	const Property* SubIdea::GetProperty(Property::Type type) const
	{
		for (const Property& prop : m_Properties)
		{
			if (prop.GetType() == type)
			{
				return &prop;
			}
		}
		for (const Property& prop : m_Idea->m_Properties)
		{
			if (prop.GetType() == type)
			{
				return &prop;
			}
		}
		return nullptr;
	}
}