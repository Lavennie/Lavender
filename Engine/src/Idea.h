#pragma once
#include <vector>
#include "Property.h"

namespace Lavender
{
	using namespace std;

	class Idea
	{
		friend class SubIdea;
		friend class Info;
	protected:
		vector<Property> m_Properties;

	public:
		Idea();
		Idea(const void* nothing);
		virtual const Property* GetProperty(Property::Type type) const;

		template <class T, class... Arguments>
		void AddProperty(Property::Type type, Arguments&&... parameters)
		{
			T propertyValue(parameters...);
			m_Properties.emplace_back(type, &propertyValue);
		}
	};
}