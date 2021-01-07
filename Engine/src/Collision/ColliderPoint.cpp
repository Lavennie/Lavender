#include <typeinfo>
#include "ColliderPoint.h"

namespace Lavender
{
	ColliderPoint::ColliderPoint(Vector3 center) : m_Center(center) {}

	const Vector3& ColliderPoint::GetCenter() const
	{
		return m_Center;
	}
}