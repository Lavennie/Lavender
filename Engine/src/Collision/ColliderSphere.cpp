#include "ColliderSphere.h"

namespace Lavender
{
	ColliderSphere::ColliderSphere(Vector3 center, float radius) : ColliderPoint(center), m_Radius(radius) {}

	float ColliderSphere::GetRadius() const
	{
		return m_Radius;
	}
}