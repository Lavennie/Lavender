#pragma once
#include "ColliderPoint.h"

namespace Lavender
{
	class ColliderSphere : public ColliderPoint
	{
	private:
		float m_Radius;

	public:
		ColliderSphere(Vector3 center, float radius);
		float GetRadius() const;
	};
}

