#pragma once
#include "Math/Matrix4.h"

namespace Lavender
{
	class Camera
	{
	private:
		Matrix4 m_ProjectionMatrix;
	public:
		Vector3 position;
		Quaternion rotation;
	public:
		Camera(float fov, float ar, float zNear, float zFar);
		Camera(float left, float right, float bottom, float top, float zNear, float zFar);

		Matrix4 GetProjectionMatrix() const;
		void SetProjectionMatrix(float fov, float ar, float zNear, float zFar);
	};
}
