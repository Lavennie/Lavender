#pragma once
#include "Vector3.h"

namespace Lavender
{
	struct Quaternion
	{
		Vector3 v;
		float w;

		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Vector3& v, float w);
		Quaternion(float eulerX, float eulerY, float eulerZ);
		Quaternion(const Vector3& euler);
		Quaternion(const float* mat);

		void Set(float x, float y, float z, float w);
		void Set(const Vector3& v, float w);

		float GetMagnitude() const;
		Vector3 GetEulerAngles() const;

		Quaternion& Normalize();
		Quaternion& Conjugate();
		static Quaternion Normalize(const Quaternion& q);
		static Quaternion Conjugate(const Quaternion& q);

		static Quaternion FromTo(const Quaternion& from, const Quaternion& to);

		Quaternion operator*(const float a) const;
		Quaternion operator*(const Quaternion& other) const;
		Quaternion& operator*=(const float a);
		Quaternion& operator*=(const Quaternion& other);

		bool operator==(const Quaternion& other) const;
		bool operator!=(const Quaternion& other) const;

		float operator[](int index) const;
		float& operator[](int index);
	};
}