#include "Quaternion.h"
#define _USE_MATH_DEFINES
#include <cmath>

namespace Lavender
{
	Quaternion::Quaternion() : v(0, 0, 0), w(1) {}
	Quaternion::Quaternion(float x, float y, float z, float w) : v(x, y, z), w(w) {}
	Quaternion::Quaternion(const Vector3& v, float w) : v(v), w(w) {}
	Quaternion::Quaternion(float eulerX, float eulerY, float eulerZ) 
	{
		double c1 = cos(eulerY / 2.0f);
		double s1 = sin(eulerY / 2.0f);
		double c2 = cos(eulerX / 2.0f);
		double s2 = sin(eulerX / 2.0f);
		double c3 = cos(eulerZ / 2.0f);
		double s3 = sin(eulerZ / 2.0f);
		w = c1 * c2 * c3 - s1 * s2 * s3;
		v = Vector3(
			c1 * c2 * s3 + s1 * s2 * c3,
			s1 * c2 * c3 + c1 * s2 * s3,
			c1 * s2 * c3 - s1 * c2 * s3);
	}
	// Construct Quaternion from angles over axises in degress
	Quaternion::Quaternion(const Vector3& euler)
	{
		double c1 = cos((euler.y * (M_PI / 180.0f)) / 2.0f);
		double s1 = sin((euler.y * (M_PI / 180.0f)) / 2.0f);
		double c2 = cos((euler.x * (M_PI / 180.0f)) / 2.0f);
		double s2 = sin((euler.x * (M_PI / 180.0f)) / 2.0f);
		double c3 = cos((euler.z * (M_PI / 180.0f)) / 2.0f);
		double s3 = sin((euler.z * (M_PI / 180.0f)) / 2.0f);
		w = c1 * c2 * c3 - s1 * s2 * s3;
		v = Vector3(
			c1 * c2 * s3 + s1 * s2 * c3,
			s1 * c2 * c3 + c1 * s2 * s3,
			c1 * s2 * c3 - s1 * c2 * s3);
	}
	Quaternion::Quaternion(const float* mat)
	{
		// mat[row, column]
		float trace = mat[0] + mat[5] + mat[10]; // mat[0, 0], mat[1, 1], mat[2, 2]

		if (trace > 0)
		{
			float S = sqrt(trace + 1.0f) * 2.0f; // S=4*qw 
			w = 0.25f * S;
			v = Vector3(
				(mat[6] - mat[9]) / S,  // (mat[2, 1] - mat[1, 2]) / S
				(mat[8] - mat[2]) / S,  // (mat[0, 2] - mat[2, 0]) / S
				(mat[1] - mat[4]) / S); // (mat[1, 0] - mat[0, 1]) / S
		}
		else if ((mat[0] > mat[5]) & (mat[0] > mat[10])) // (mat[0, 0] > mat[1, 1]) & (mat[0, 0] > mat[2, 2])
		{
			float S = sqrt(1.0f + mat[0] - mat[5] - mat[10]) * 2; // S=4*qx   // sqrt(1 + mat[0, 0] - mat[1, 1] - mat[2, 2])
			w = (mat[6] - mat[9]) / S;  // (mat[2, 1] - mat[1, 2]) / S
			v = Vector3(
				0.25f * S,
				(mat[4] + mat[1]) / S,  // (mat[0, 1] + mat[1, 0]) / S
				(mat[8] + mat[2]) / S); // (mat[0, 2] + mat[2, 0]) / S
		}
		else if (mat[5] > mat[10])
		{
			float S = sqrt(1.0f + mat[5] - mat[0] - mat[10]) * 2; // S=4*qy   // sqrt(1 + mat[1, 1] - mat[0, 0] - mat[2, 2])
			w = (mat[8] - mat[2]) / S;  // (mat[0, 2] - mat[2, 0]) / S
			v = Vector3(
				(mat[4] + mat[1]) / S,  // (mat[0, 1] + mat[1, 0]) / S
				0.25f * S,
				(mat[9] + mat[6]) / S); // (mat[1, 2] + mat[2, 1]) / S
		}
		else
		{
			float S = sqrt(1.0f + mat[10] - mat[0] - mat[5]) * 2; // S=4*qz   // sqrt(1 + mat[2, 2] - mat[0, 0] - mat[1, 1])
			w = (mat[1] - mat[4]) / S;  // (mat[1, 0] - mat[0, 1]) / S
			v = Vector3(
				(mat[8] + mat[2]) / S,  // (mat[0, 2] + mat[2, 0]) / S
				(mat[9] + mat[6]) / S,  // (mat[1, 2] + mat[2, 1]) / S
				0.25f * S);
		}
	}

	void Quaternion::Set(float x, float y, float z, float w)
	{
		this->v.x = x; 
		this->v.y = y; 
		this->v.z = z; 
		this->w = w;
	}
	void Quaternion::Set(const Vector3& v, float w)
	{
		this->v.x = v.x;
		this->v.y = v.y;
		this->v.z = v.z;
		this->w = w;
	}

	float Quaternion::GetMagnitude() const
	{
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + w * w);
	}
	Vector3 Quaternion::GetEulerAngles() const
	{
		float sqw = w * w;
		float sqx = v.x * v.x;
		float sqy = v.y * v.y;
		float sqz = v.z * v.z;
		float unit = sqx + sqy + sqz + sqw; // if normalized is one, otherwise is correction factor
		float test = v.x * v.y + v.z * w;
		if (test > 0.499 * unit)
		{
			// singularity at north pole
			return Vector3(M_PI / 2.0f, 2.0f * atan2(v.x, w), 0.0f);
		}
		if (test < -0.499 * unit)
		{
			// singularity at south pole
			return Vector3(-M_PI / 2.0f, -2.0f * atan2(v.x, w), 0.0f);
		}
		return Vector3(
			asin(2.0f * test / unit),
			atan2(2.0f * v.y * w - 2.0f * v.x * v.z, sqx - sqy - sqz + sqw),
			atan2(2.0f * v.x * w - 2.0f * v.y * v.z, -sqx + sqy - sqz + sqw));
	}

	Quaternion& Quaternion::Normalize()
	{
		float d = GetMagnitude();

		this->v.x /= d;
		this->v.y /= d;
		this->v.z /= d;
		this->w /= d;

		return *this;
	}
	Quaternion& Quaternion::Conjugate()
	{
		this->v.x = -v.x;
		this->v.y = -v.y;
		this->v.z = -v.z;

		return *this;
	}
	Quaternion Quaternion::Normalize(const Quaternion& q)
	{
		float d = q.GetMagnitude();

		return Quaternion(q.v.x / d, q.v.y / d, q.v.z / d, q.w / d);
	}
	Quaternion Quaternion::Conjugate(const Quaternion& q)
	{
		return Quaternion(-q.v.x, -q.v.y, -q.v.z, q.w);
	}

	Quaternion Quaternion::FromTo(const Quaternion& from, const Quaternion& to)
	{
		return to * Conjugate(from);
	}

	Quaternion Quaternion::operator*(const float a) const
	{
		return Quaternion(v.x * a, v.y * a, v.z * a, w * a);
	}
	Quaternion Quaternion::operator*(const Quaternion& other) const
	{
		return Quaternion(v * other.w + other.v * w + v.Cross(other.v), w * other.w - v.Dot(other.v));
	}
	Quaternion& Quaternion::operator*=(const float a)
	{
		v.x *= a;
		v.y *= a;
		v.z *= a;
		w *= a;

		return *this;
	}
	Quaternion& Quaternion::operator*=(const Quaternion& other)
	{
		v = v * other.w + other.v * w + v.Cross(other.v);
		w = w * other.w - v.Dot(other.v);

		return *this;
	}

	bool Quaternion::operator==(const Quaternion& other) const
	{
		return v == other.v && w == other.w;
	}
	bool Quaternion::operator!=(const Quaternion& other) const
	{
		return v != other.v || w != other.w;
	}

	float Quaternion::operator[](int index) const
	{
		return (&v.x)[index];
	}
	float& Quaternion::operator[](int index)
	{
		return (&v.x)[index];
	}
}