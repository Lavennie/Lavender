#pragma once
#include <typeinfo>
#include "Math/Vector3.h"
#include "Collider.h"
#include "ColliderPoint.h"
#include "ColliderSphere.h"
#include "Real.h"

namespace Lavender
{
	struct Collision
	{
	public:
		const bool colliding;
		const Vector3 point;

	public:
		Collision(bool colliding, Vector3 point);

		static Collision TestForCollision(const Real* r1, const Real* r2);
		template <class T1, class T2>
		static Collision TestForCollision(const Real* r1, const T1* c1, const Real* r2, const T2* c2) { }
	};
	template<>
	Collision Collision::TestForCollision<ColliderPoint, ColliderPoint>(const Real* r1, const ColliderPoint* c1, const Real* r2, const ColliderPoint* c2);
	template <>
	Collision Collision::TestForCollision<ColliderPoint, ColliderSphere>(const Real* r1, const ColliderPoint* c1, const Real* r2, const ColliderSphere* c2);
	template <>
	Collision Collision::TestForCollision<ColliderSphere, ColliderPoint>(const Real* r1, const ColliderSphere* c1, const Real* r2, const ColliderPoint* c2);
	template <>
	Collision Collision::TestForCollision<ColliderSphere, ColliderSphere>(const Real* r1, const ColliderSphere* c1, const Real* r2, const ColliderSphere* c2);
}

