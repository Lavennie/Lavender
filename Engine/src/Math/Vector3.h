#pragma once

namespace Lavender
{
	struct Vector3
	{
		float x, y, z;

		Vector3();
		Vector3(float x, float y, float z);

		void Set(float x, float y, float z);
		float Length() const;
		Vector3& Normalize();
		Vector3 Normalized() const;
		float Dot(const Vector3& vec) const;
		Vector3 Cross(const Vector3& vec) const;

		Vector3 operator-() const;
		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;
		Vector3& operator+=(const Vector3& other);
		Vector3& operator-=(const Vector3& other);

		Vector3 operator*(const float a) const;
		Vector3 operator*(const Vector3& other) const;
		Vector3& operator*=(const float a);
		Vector3& operator*=(const Vector3& other);

		Vector3 operator/(const float a) const;
		Vector3& operator/=(const float a);

		bool operator==(const Vector3& other) const;
		bool operator!=(const Vector3& other) const;

		float operator[](int index) const;
		float& operator[](int index);
	};
}
