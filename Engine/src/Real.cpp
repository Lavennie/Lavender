#include "Real.h"

namespace Lavender
{
	Real::Real(const Info* info) : 
		m_Info(info)
	{ }

	Matrix4 Real::GetModelMatrix() const
	{
		return Matrix4::InitTranslation(m_Info->GetIdea()->GetPosition()) * 
			Matrix4::InitRotation(m_Info->GetIdea()->GetRotation()) * 
			Matrix4::InitScale(m_Info->GetIdea()->GetScale());
	}

	const Collider* Real::GetCollider(unsigned int colliderIndex) const
	{
		if (colliderIndex >= m_Colliders.size())
		{
			return nullptr;
		}
		return m_Colliders[colliderIndex].get();
	}
	const ColliderPoint* Real::AddCollider(const Vector3& center)
	{
		m_Colliders.push_back(move(make_unique<ColliderPoint>(center)));
		return (ColliderPoint*)m_Colliders.back().get();
	}
	const ColliderSphere* Real::AddCollider(const Vector3& center, float radius)
	{
		m_Colliders.push_back(move(make_unique<ColliderSphere>(center, radius)));
		return (ColliderSphere*)m_Colliders.back().get();
	}

	const Info* Real::GetInfo() const { return m_Info; }
	const Idea* Real::GetIdea() const { return m_Info->GetIdea(); }
}