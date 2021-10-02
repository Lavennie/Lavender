#pragma once
#define COLLISION_ENTER 0
#define COLLISION_STAY 1
#define COLLISION_EXIT 2
#include <vector>
#include "Collision.h"
#include "Real.h"
#include "Collider.h"

namespace Lavender
{
	/// <summary>
	/// First value is data about the collision and second is state of collision (ENTER, STAY, EXIT)
	/// </summary>
	typedef pair<Collision, unsigned char> CollisionInfo;

	class CollisionList final
	{
	private:
		vector<CollisionInfo> m_Collisions;

	private:
		static CollisionList& Instance();
	public:
		CollisionList() {}
		~CollisionList() {}

		void CollisionsMarkForClear();
		bool TryRegisterCollision(const Real& r1, const Real& r2);
		void CollisionsMarkExiting();
		void ClearInvalidCollisions();
		CollisionInfo* ContainsCollision(const Real& r1, const Real& r2);

		void InvokeEvents();

		static const CollisionInfo* CollisionIs(const Real& r1, const Real& r2);
		static const Collision* CollisionEnter(const Real& r1, const Real& r2);
		static const Collision* CollisionStay(const Real& r1, const Real& r2);
		static const Collision* CollisionExit(const Real& r1, const Real& r2);
	};
}

