#include "Idea.h"

namespace Lavender
{
	Idea::Idea() : m_Properties() { }
	Idea::Idea(const void* nothing) : Idea() { }

	const Property* Idea::GetProperty(Property::Type type) const
	{
		for (const Property& prop : m_Properties)
		{
			if (prop.GetType() == type)
			{
				return &prop;
			}
		}
		return nullptr;
	}
}