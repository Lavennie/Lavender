#include "Collision.h"
namespace Lavender
{
	Collision::Collision() : colliding(false) {}
	Collision::Collision(bool colliding, Vector3 point, ColliderRef c1, ColliderRef c2) : colliding(colliding), point(point), c1(c1), c2(c2) {}

	const Real* Collision::GetObject1() { return get<0>(c1); }
	const Real* Collision::GetObject2() { return get<0>(c2); }

	Collision Collision::TestForCollision(const Real* r1, const Real* r2)
	{
		if (r1->GetCollider(0) != nullptr && r2->GetCollider(0) != nullptr)
		{
			if (r1->GetCollider(0)->GetType() == Collider::Type::Sphere)
			{
				if (r2->GetCollider(0)->GetType() == Collider::Type::Sphere)
				{
					return TestForCollision<ColliderSphere, ColliderSphere>(r1, 0, (const ColliderSphere*)r1->GetCollider(0), r2, 0, (const ColliderSphere*)r2->GetCollider(0));
				}
				else if (r2->GetCollider(0)->GetType() == Collider::Type::Point)
				{
					return TestForCollision<ColliderSphere, ColliderPoint>(r1, 0, (const ColliderSphere*)r1->GetCollider(0), r2, 0, (const ColliderSphere*)r2->GetCollider(0));
				}
			}
			else if (r1->GetCollider(0)->GetType() == Collider::Type::Point)
			{
				if (r2->GetCollider(0)->GetType() == Collider::Type::Sphere)
				{
					return TestForCollision<ColliderPoint, ColliderSphere>(r1, 0, (const ColliderSphere*)r1->GetCollider(0), r2, 0, (const ColliderSphere*)r2->GetCollider(0));
				}
				else if (r2->GetCollider(0)->GetType() == Collider::Type::Point)
				{
					return TestForCollision<ColliderPoint, ColliderPoint>(r1, 0, (const ColliderSphere*)r1->GetCollider(0), r2, 0, (const ColliderSphere*)r2->GetCollider(0));
				}
			}
		}
		return Collision();
		
	}
	template <>
	Collision Collision::TestForCollision<ColliderPoint, ColliderPoint>(const Real* r1, unsigned char i1, const ColliderPoint* c1, const Real* r2, unsigned char i2, const ColliderPoint* c2)
	{
		Vector3 center1 = r1->GetIdea()->GetPosition() + (r1->GetIdea()->GetRotation() * c1->GetCenter()) * r1->GetIdea()->GetScale();
		Vector3 center2 = r2->GetIdea()->GetPosition() + (r2->GetIdea()->GetRotation() * c2->GetCenter()) * r2->GetIdea()->GetScale();
		return Collision(center1 == center2, (center1 + center2) / 2.0f, make_tuple(r1, i1), make_tuple(r2, i2));
	}
	template <>
	Collision Collision::TestForCollision<ColliderPoint, ColliderSphere>(const Real* r1, unsigned char i1, const ColliderPoint* c1, const Real* r2, unsigned char i2, const ColliderSphere* c2)
	{
		Vector3 center1 = r1->GetIdea()->GetPosition() + (r1->GetIdea()->GetRotation() * c1->GetCenter()) * r1->GetIdea()->GetScale();
		Vector3 center2 = r2->GetIdea()->GetPosition() + (r2->GetIdea()->GetRotation() * c2->GetCenter()) * r2->GetIdea()->GetScale();
		return Collision((center1 - center2).Length() - c2->GetRadius() <= 0, (center1 + center2) / 2.0f, make_tuple(r1, i1), make_tuple(r2, i2));
	}
	template <>
	Collision Collision::TestForCollision<ColliderSphere, ColliderPoint>(const Real* r1, unsigned char i1, const ColliderSphere* c1, const Real* r2, unsigned char i2, const ColliderPoint* c2)
	{
		Vector3 center1 = r1->GetIdea()->GetPosition() + (r1->GetIdea()->GetRotation() * c1->GetCenter()) * r1->GetIdea()->GetScale();
		Vector3 center2 = r2->GetIdea()->GetPosition() + (r2->GetIdea()->GetRotation() * c2->GetCenter()) * r2->GetIdea()->GetScale();
		return Collision((center1 - center2).Length() - c1->GetRadius() <= 0, (center1 + center2) / 2.0f, make_tuple(r1, i1), make_tuple(r2, i2));
	}
	template <>
	Collision Collision::TestForCollision<ColliderSphere, ColliderSphere>(const Real* r1, unsigned char i1, const ColliderSphere* c1, const Real* r2, unsigned char i2, const ColliderSphere* c2)
	{
		Vector3 center1 = r1->GetIdea()->GetPosition() + (r1->GetIdea()->GetRotation() * c1->GetCenter()) * r1->GetIdea()->GetScale();
		Vector3 center2 = r2->GetIdea()->GetPosition() + (r2->GetIdea()->GetRotation() * c2->GetCenter()) * r2->GetIdea()->GetScale();
		return Collision((center1 - center2).Length() - c1->GetRadius() - c2->GetRadius() <= 0, (center1 + center2) / 2.0f, make_tuple(r1, i1), make_tuple(r2, i2));
	}
}