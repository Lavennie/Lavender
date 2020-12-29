#pragma once
#include <vector>
#include "Info.h"
#include "Component.h"
#include "Math/Matrix4.h"

namespace Lavender
{
	using namespace std;

	// Entity in REAL layer. Has children that build a hiearachy
	class Real
	{
	private:
		const Info* m_Info;
		vector<shared_ptr<Real>> m_Children;
		vector<shared_ptr<Component>> m_Components;

	public:
		Real(const Info* info);

		Matrix4 GetModelMatrix() const;

		template <class T>
		const T* GetProperty(Property::Type type) const
		{
			const Property* prop = m_Info->GetProperty(type);
			if (prop == nullptr) { return nullptr; }
			return (T*)prop->GetValue();
		}
	};
}


