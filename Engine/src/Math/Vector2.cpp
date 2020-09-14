#include "Vector2.h"
#include <cmath>

namespace Lavender
{
	Vector2::Vector2() : x(0), y(0) {}
	Vector2::Vector2(float x, float y) : x(x), y(y) {}

	void Vector2::Set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	float Vector2::Length() const
	{
		return sqrtf(x * x + y * y);
	}
	Vector2& Vector2::Normalize()
	{
		float xySquared = x * x + y * y;

		x /= xySquared;
		y /= xySquared;
		return *this;
	}
	float Vector2::Dot(const Vector2& vec) const
	{
		return x * vec.x + y * vec.y;
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2(-x, -y);
	}
	Vector2 Vector2::operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 Vector2::operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2& Vector2::operator+=(const Vector2& other)
	{
		x += other.x; y += other.y;
		return *this;
	}
	Vector2& Vector2::operator-=(const Vector2& other)
	{
		x -= other.x; y -= other.y;
		return *this;
	}

	Vector2 Vector2::operator*(const float a) const
	{
		return Vector2(x * a, y * a);
	}
	Vector2 Vector2::operator*(const Vector2& other) const
	{
		return Vector2(x * other.x, y * other.y);
	}
	Vector2& Vector2::operator*=(const float a)
	{
		x *= a; y *= a;
		return *this;
	}
	Vector2& Vector2::operator*=(const Vector2& other)
	{
		x *= other.x; y *= other.y;
		return *this;
	}

	Vector2 Vector2::operator/(const float a) const
	{
		return Vector2(x / a, y / a);
	}
	Vector2& Vector2::operator/=(const float a)
	{
		x /= a; y /= a;
		return *this;
	}

	bool Vector2::operator==(const Vector2& other) const
	{
		return (x == other.x) && (y == other.y);
	}
	bool Vector2::operator!=(const Vector2& other) const
	{
		return (x != other.x) || (y != other.y);
	}

	float Vector2::operator[](int index) const
	{
		return (&x)[index];
	}
	float& Vector2::operator[](int index)
	{
		return (&x)[index];
	}
}