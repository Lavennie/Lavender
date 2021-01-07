#include "Collision.h"
namespace Lavender
{
	Collision::Collision(bool colliding, Vector3 point) : colliding(colliding), point(point) { }

	Collision Collision::TestForCollision(const Real* r1, const Real* r2)
	{
		if (dynamic_cast<const ColliderSphere*>(r1->GetCollider(0)) != nullptr)
		{
			if (dynamic_cast<const ColliderSphere*>(r2->GetCollider(0)) != nullptr)
			{
				return TestForCollision<ColliderSphere, ColliderSphere>(r1, (const ColliderSphere*)r1->GetCollider(0), r2, (const ColliderSphere*)r2->GetCollider(0));
			}
			else if (dynamic_cast<const ColliderPoint*>(r2->GetCollider(0)) != nullptr)
			{
				return TestForCollision<ColliderSphere, ColliderPoint>(r1, (const ColliderSphere*)r1->GetCollider(0), r2, (const ColliderPoint*)r2->GetCollider(0));
			}
		}
		else if (dynamic_cast<const ColliderPoint*>(r1->GetCollider(0)) != nullptr)
		{
			if (dynamic_cast<const ColliderSphere*>(r2->GetCollider(0)) != nullptr)
			{
				return TestForCollision<ColliderPoint, ColliderSphere>(r1, (const ColliderPoint*)r1->GetCollider(0), r2, (const ColliderSphere*)r2->GetCollider(0));
			}
			else if (dynamic_cast<const ColliderPoint*>(r2->GetCollider(0)) != nullptr)
			{
				return TestForCollision<ColliderPoint, ColliderPoint>(r1, (const ColliderPoint*)r1->GetCollider(0), r2, (const ColliderPoint*)r2->GetCollider(0));
			}
		}
		else
		{
			return Collision(false, Vector3(0, 0, 0));
		}
	}
	template <>
	Collision Collision::TestForCollision<ColliderPoint, ColliderPoint>(const Real* r1, const ColliderPoint* c1, const Real* r2, const ColliderPoint* c2)
	{
		Vector3 center1 = r1->GetIdea()->GetPosition() + (r1->GetIdea()->GetRotation() * c1->GetCenter()) * r1->GetIdea()->GetScale();
		Vector3 center2 = r2->GetIdea()->GetPosition() + (r2->GetIdea()->GetRotation() * c2->GetCenter()) * r2->GetIdea()->GetScale();
		return Collision(center1 == center2, (center1 + center2) / 2.0f);
	}
	template <>
	Collision Collision::TestForCollision<ColliderPoint, ColliderSphere>(const Real* r1, const ColliderPoint* c1, const Real* r2, const ColliderSphere* c2)
	{
		Vector3 center1 = r1->GetIdea()->GetPosition() + (r1->GetIdea()->GetRotation() * c1->GetCenter()) * r1->GetIdea()->GetScale();
		Vector3 center2 = r2->GetIdea()->GetPosition() + (r2->GetIdea()->GetRotation() * c2->GetCenter()) * r2->GetIdea()->GetScale();
		return Collision((center1 - center2).Length() - c2->GetRadius() <= 0, (center1 + center2) / 2.0f);
	}
	template <>
	Collision Collision::TestForCollision<ColliderSphere, ColliderPoint>(const Real* r1, const ColliderSphere* c1, const Real* r2, const ColliderPoint* c2)
	{
		Vector3 center1 = r1->GetIdea()->GetPosition() + (r1->GetIdea()->GetRotation() * c1->GetCenter()) * r1->GetIdea()->GetScale();
		Vector3 center2 = r2->GetIdea()->GetPosition() + (r2->GetIdea()->GetRotation() * c2->GetCenter()) * r2->GetIdea()->GetScale();
		return Collision((center1 - center2).Length() - c1->GetRadius() <= 0, (center1 + center2) / 2.0f);
	}
	template <>
	Collision Collision::TestForCollision<ColliderSphere, ColliderSphere>(const Real* r1, const ColliderSphere* c1, const Real* r2, const ColliderSphere* c2)
	{
		Vector3 center1 = r1->GetIdea()->GetPosition() + (r1->GetIdea()->GetRotation() * c1->GetCenter()) * r1->GetIdea()->GetScale();
		Vector3 center2 = r2->GetIdea()->GetPosition() + (r2->GetIdea()->GetRotation() * c2->GetCenter()) * r2->GetIdea()->GetScale();
		return Collision((center1 - center2).Length() - c1->GetRadius() - c2->GetRadius() <= 0, (center1 + center2) / 2.0f);
	}
}