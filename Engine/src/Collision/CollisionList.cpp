#include "CollisionList.h"
#include "Core.h"

namespace Lavender
{
	CollisionList& CollisionList::Instance() { return Core::GetInstance()->GetCollisions(); }

	void CollisionList::ClearCollisions()
	{
		Instance().m_Collisions.clear();
	}
	bool CollisionList::TryRegisterCollision(const Real& r1, const Real& r2)
	{
		Collision collision = Collision::TestForCollision(&r1, &r2);
		if (collision.colliding)
		{
			Instance().m_Collisions.push_back(move(collision));
			return true;
		}
		return false;
	}

}