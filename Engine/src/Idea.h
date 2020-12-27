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
		void AddProperty(Property::Type type, void* value);
	};
}