#pragma once
#include <vector>
#include "Collision.h"
#include "Real.h"
#include "Collider.h"

namespace Lavender
{
	class CollisionList final
	{
	private:
		vector<Collision> m_Collisions;

	private:
		static CollisionList& Instance();
	public:
		CollisionList() {}
		~CollisionList() {}

		static void ClearCollisions();
		static bool TryRegisterCollision(const Real& r1, const Real& r2);
	};
}

