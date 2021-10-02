#pragma once
#include <typeinfo>
#include "Math/Vector3.h"
#include "Collider.h"
#include "ColliderPoint.h"
#include "ColliderSphere.h"
#include "Real.h"

namespace Lavender
{
	using namespace std;

	/// <summary>
	/// Pointer to object and index of collider on object
	/// </summary>
	typedef tuple<const Real*, unsigned char> ColliderRef;

	struct Collision
	{
	public:
		bool colliding;
		Vector3 point;
		ColliderRef c1;
		ColliderRef c2;

	public:
		Collision();
		Collision(bool colliding, Vector3 point, ColliderRef c1, ColliderRef c2);

		const Real* GetObject1();
		const Real* GetObject2();

		static Collision TestForCollision(const Real* r1, const Real* r2);
		template <class T1, class T2>
		static Collision TestForCollision(const Real* r1, unsigned char i1, const T1* c1, const Real* r2, unsigned char i2, const T2* c2) { }
	};
	template<>
	Collision Collision::TestForCollision<ColliderPoint, ColliderPoint>(const Real* r1, unsigned char i1, const ColliderPoint* c1, const Real* r2, unsigned char i2, const ColliderPoint* c2);
	template <>
	Collision Collision::TestForCollision<ColliderPoint, ColliderSphere>(const Real* r1, unsigned char i1, const ColliderPoint* c1, const Real* r2, unsigned char i2, const ColliderSphere* c2);
	template <>
	Collision Collision::TestForCollision<ColliderSphere, ColliderPoint>(const Real* r1, unsigned char i1, const ColliderSphere* c1, const Real* r2, unsigned char i2, const ColliderPoint* c2);
	template <>
	Collision Collision::TestForCollision<ColliderSphere, ColliderSphere>(const Real* r1, unsigned char i1, const ColliderSphere* c1, const Real* r2, unsigned char i2, const ColliderSphere* c2);
}

