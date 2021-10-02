#include "CollisionList.h"
#include "Core.h"

namespace Lavender
{
	CollisionList& CollisionList::Instance() { return Core::GetInstance()->GetCollisions(); }

	void CollisionList::CollisionsMarkForClear()
	{
		for (CollisionInfo& collision : Instance().m_Collisions)
		{
			collision.first.colliding = false;
		}
	}
	bool CollisionList::TryRegisterCollision(const Real& r1, const Real& r2)
	{
		Collision collision = Collision::TestForCollision(&r1, &r2);
		if (collision.colliding)
		{
			CollisionInfo* prevCollision = ContainsCollision(r1, r2);
			// was already colliding previous iteration
			if (prevCollision != nullptr)
			{
				prevCollision->first.colliding = true;
				prevCollision->second = COLLISION_STAY;
			}
			// a new collision
			else
			{
				m_Collisions.emplace_back(move(collision), COLLISION_ENTER);
			}
			return true;
		}
		return false;
	}
	void CollisionList::CollisionsMarkExiting()
	{
		for (CollisionInfo& collision : Instance().m_Collisions)
		{
			if (collision.first.colliding == false && collision.second != COLLISION_EXIT)
			{
				collision.first.colliding = true;
				collision.second = COLLISION_EXIT;
			}
		}
	}
	void CollisionList::ClearInvalidCollisions()
	{
		m_Collisions.erase(remove_if(m_Collisions.begin(), m_Collisions.end(),
			[](const CollisionInfo& col) { return col.first.colliding == false; }), m_Collisions.end());
	}
	CollisionInfo* CollisionList::ContainsCollision(const Real& r1, const Real& r2)
	{
		for (CollisionInfo& collision : Instance().m_Collisions)
		{
			if ((get<0>(collision.first.c1) == &r1 && get<0>(collision.first.c2) == &r2) ||
				(get<0>(collision.first.c1) == &r2 && get<0>(collision.first.c2) == &r1))
			{
				return &collision;
			}
		}
		return nullptr;
	}

	void CollisionList::InvokeEvents()
	{
		for (CollisionInfo& collision : Instance().m_Collisions)
		{
			collision.first.GetObject1();
		}
	}

	const CollisionInfo* CollisionList::CollisionIs(const Real& r1, const Real& r2)
	{
		for (const CollisionInfo& collision : Instance().m_Collisions)
		{
			if ((get<0>(collision.first.c1) == &r1 && get<0>(collision.first.c2) == &r2) ||
				(get<0>(collision.first.c1) == &r2 && get<0>(collision.first.c2) == &r1))
			{
				return &collision;
			}
		}
		return nullptr;
	}
	const Collision* CollisionList::CollisionEnter(const Real& r1, const Real& r2)
	{
		const CollisionInfo* collision = CollisionIs(r1, r2);
		if (collision != nullptr && collision->second == COLLISION_ENTER)
		{
			return &collision->first;
		}
		return nullptr;
	}
	const Collision* CollisionList::CollisionStay(const Real& r1, const Real& r2)
	{
		const CollisionInfo* collision = CollisionIs(r1, r2);
		if (collision != nullptr && collision->second == COLLISION_STAY)
		{
			return &collision->first;
		}
		return nullptr;
	}
	const Collision* CollisionList::CollisionExit(const Real& r1, const Real& r2)
	{
		const CollisionInfo* collision = CollisionIs(r1, r2);
		if (collision != nullptr && collision->second == COLLISION_EXIT)
		{
			return &collision->first;
		}
		return nullptr;
	}
}