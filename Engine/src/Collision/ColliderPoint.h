#pragma once
#include "Collider.h"
#include "Math/Vector3.h"

namespace Lavender
{
	class ColliderPoint : public Collider
	{
	private:
		Vector3 m_Center;

	public:
		ColliderPoint(Vector3 center);
		const Vector3& GetCenter() const;

		Collider::Type GetType() const override;
	};
}