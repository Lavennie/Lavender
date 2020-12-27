#include "Camera.h"
#define _USE_MATH_DEFINES
#include <cmath>

namespace Lavender
{
	Camera::Camera(float fov, float ar, float zNear, float zFar) : position(0, 0, 0), rotation(0, 0, 0, 1)
	{
		m_ProjectionMatrix = Matrix4::InitPerspectiveProjection(fov * (M_PI / 180.0f), ar, zNear, zFar);
	}

	Matrix4 Camera::GetProjectionMatrix() const
	{
		return m_ProjectionMatrix * Matrix4::InitRotation(Quaternion::Conjugate(rotation)) * Matrix4::InitTranslation(-position);
	}
}