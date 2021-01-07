#include "Idea.h"

namespace Lavender
{
	Idea::Idea() : Idea({ 0, 0, 0 }, { 0, 0, 0, 1 }, { 1, 1, 1 }) {}
	Idea::Idea(const Vector3& position, const Quaternion& rotation, const Vector3& scale) 
		: m_Pos(position), m_Rot(rotation), m_Scl(scale){ }

	const Vector3& Idea::GetPosition() const { return m_Pos; }
	const Quaternion& Idea::GetRotation() const { return m_Rot; }
	const Vector3& Idea::GetScale() const { return m_Scl; }

	void Idea::SetPosition(float x, float y, float z) { m_Pos = Vector3(x, y, z); }
	void Idea::SetRotation(float x, float y, float z) { m_Rot = Quaternion(x, y, z); }
	void Idea::SetScale(float x, float y, float z) { m_Scl = Vector3(x, y, z); }
	void Idea::SetPosition(const Vector3& position) { m_Pos = position; }
	void Idea::SetRotation(const Quaternion& rotation) { m_Rot = rotation; }
	void Idea::SetScale(const Vector3& scale) { m_Scl = scale; }

	const Property* Idea::GetProperty(Property::Type type) const
	{
		for (const Property& prop : m_Properties)
		{
			if (prop.GetType() == type)
			{
				return &prop;
			}
		}
		return nullptr;
	}
	void Idea::SetProperty(Property::Type type, const Property* value)
	{
		for (Property& prop : m_Properties)
		{
			if (prop.GetType() == type)
			{
				// set value;
			}
		}
	}
}