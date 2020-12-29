#include "Real.h"

namespace Lavender
{
	Real::Real(const Info* info) : 
		m_Info(info)
	{ }

	Matrix4 Real::GetModelMatrix() const
	{
		const PropertyVector3* position = GetProperty<PropertyVector3>(Property::Type::Position);
		const PropertyRotation* rotation = GetProperty<PropertyRotation>(Property::Type::Rotation);
		const PropertyVector3* scale = GetProperty<PropertyVector3>(Property::Type::Scale);

		Matrix4 mat;
		if (position != nullptr)
		{
			mat *= Matrix4::InitTranslation(position->GetValue());
		}
		if (rotation != nullptr)
		{
			mat *= Matrix4::InitRotation(rotation->GetValue());
		}
		if (scale != nullptr)
		{
			mat *= Matrix4::InitScale(scale->GetValue());
		}
		return mat;
	}
}