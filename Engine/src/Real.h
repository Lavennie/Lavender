#pragma once
#include <vector>
#include "Info.h"
#include "Component.h"
#include "Math/Matrix4.h"
#include "Collision/Collider.h"
#include "Collision/ColliderPoint.h"
#include "Collision/ColliderSphere.h"

namespace Lavender
{
	using namespace std;

	// Entity in REAL layer. Has children that build a hiearachy
	class Real
	{
	private:
		const Info* m_Info;
		vector<unique_ptr<Collider>> m_Colliders;

	public:
		Real(const Info* info);

		Matrix4 GetModelMatrix() const;

		const Collider* GetCollider(unsigned int colliderIndex) const;
		const ColliderPoint* AddCollider(const Vector3& center);
		const ColliderSphere* AddCollider(const Vector3& center, float radius);

		const Info* GetInfo() const;
		const Idea* GetIdea() const;

		template <class T>
		const T* GetProperty(Property::Type type) const
		{
			const Property* prop = m_Info->GetProperty(type);
			if (prop == nullptr) { return nullptr; }
			return (T*)prop->GetValue();
		}
	};
}


