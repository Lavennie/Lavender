#pragma once

namespace Lavender
{
	struct Vector2
	{
		float x, y;

		Vector2();
		Vector2(float x, float y);

		void Set(float x, float y);
		float Length() const;
		Vector2& Normalize();
		float Dot(const Vector2& vec) const;

		Vector2 operator-() const;
		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);

		Vector2 operator*(const float a) const;
		Vector2 operator*(const Vector2& other) const;
		Vector2& operator*=(const float a);
		Vector2& operator*=(const Vector2& other);

		Vector2 operator/(const float a) const;
		Vector2& operator/=(const float a);

		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;

		float operator[](int index) const;
		float& operator[](int index);
	};
}