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

		void Normalize();
		Quaternion Normalized();
		void Conjugate();
		Quaternion Conjugated();
		static Quaternion Normalize(const Quaternion& q);
		static Quaternion Conjugate(const Quaternion& q);

		static Quaternion FromTo(const Quaternion& from, const Quaternion& to);

		/// <summary>
		/// Multiply two Quaternions without narmalizing at end
		/// </summary>
		/// <param name="q1"></param>
		/// <param name="q2"></param>
		/// <returns>q1 * q2</returns>
		static Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);

		Quaternion operator*(const float a) const;
		Vector3 operator*(const Vector3& other) const;
		Quaternion operator*(const Quaternion& other) const;
		Quaternion& operator*=(const float a);
		Quaternion& operator*=(const Quaternion& other);

		bool operator==(const Quaternion& other) const;
		bool operator!=(const Quaternion& other) const;

		float operator[](int index) const;
		float& operator[](int index);
	};
}