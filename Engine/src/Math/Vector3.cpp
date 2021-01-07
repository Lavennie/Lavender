#include "Vector3.h"
#include <cmath>

namespace Lavender
{
	Vector3::Vector3() : x(0), y(0), z(0) {}
	Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	void Vector3::Set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float Vector3::Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}
	Vector3& Vector3::Normalize()
	{
		float length = Length();

		x /= length;
		y /= length;
		z /= length;
		return *this;
	}
	Vector3 Vector3::Normalized() const
	{
		float length = Length();
		return Vector3(x / length, y / length, z / length);
	}
	float Vector3::Dot(const Vector3& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}
	Vector3 Vector3::Cross(const Vector3& vec) const
	{
		return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}
	Vector3 Vector3::operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
	Vector3 Vector3::operator-(const Vector3& other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}
	Vector3& Vector3::operator+=(const Vector3& other)
	{
		x += other.x; y += other.y; z += other.z;
		return *this;
	}
	Vector3& Vector3::operator-=(const Vector3& other)
	{
		x -= other.x; y -= other.y; z -= other.z;
		return *this;
	}

	Vector3 Vector3::operator*(const float a) const
	{
		return Vector3(x * a, y * a, z * a);
	}
	Vector3 Vector3::operator*(const Vector3& other) const
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}
	Vector3& Vector3::operator*=(const float a)
	{
		x *= a; y *= a; z *= a;
		return *this;
	}
	Vector3& Vector3::operator*=(const Vector3& other)
	{
		x *= other.x; y *= other.y; z *= other.z;
		return *this;
	}

	Vector3 Vector3::operator/(const float a) const
	{
		return Vector3(x / a, y / a, z / a);
	}
	Vector3& Vector3::operator/=(const float a)
	{
		x /= a; y /= a; z /= a;
		return *this;
	}

	bool Vector3::operator==(const Vector3& other) const
	{
		return (x == other.x) && (y == other.y) && (z == other.z);
	}
	bool Vector3::operator!=(const Vector3& other) const
	{
		return (x != other.x) || (y != other.y) || (z != other.z);
	}

	float Vector3::operator[](int index) const
	{
		return (&x)[index];
	}
	float& Vector3::operator[](int index)
	{
		return (&x)[index];
	}
}