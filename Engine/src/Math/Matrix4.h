#pragma once
#include "Vector3.h"
#include "Quaternion.h"

namespace Lavender
{
	// The elements of the matrix are stored as column major order.
	// | 0 2 |    | 0 3 6 |    |  0  4  8 12 |
	// | 1 3 |    | 1 4 7 |    |  1  5  9 13 |
	//            | 2 5 8 |    |  2  6 10 14 |
	//                         |  3  7 11 15 |
	class Matrix4
	{
	private:
		float m[16];
	public:
		Matrix4();
		Matrix4(const float src[16]);
		// Values are stored column-major order
		Matrix4(float m00, float m01, float m02, float m03, // 1st column
			float m04, float m05, float m06, float m07, // 2nd column
			float m08, float m09, float m10, float m11, // 3rd column
			float m12, float m13, float m14, float m15);// 4th column

		void Set(const float src[16]);
		void Set(float m00, float m01, float m02, float m03, // 1st column
			float m04, float m05, float m06, float m07, // 2nd column
			float m08, float m09, float m10, float m11, // 3rd column
			float m12, float m13, float m14, float m15);// 4th column

		void SetRow(int index, const float row[4]);
		void SetRow(int index, const Vector3& v);
		void SetColumn(int index, const float col[4]);
		void SetColumn(int index, const Vector3& v);

		const float* Get() const;
		const void GetTranspose(float* tm);                        // return transposed matrix

		Matrix4& Identity();
		Matrix4& Transpose();                            // transpose itself and return reference

		static Matrix4 InitTranslation(const Vector3& translation);
		static Matrix4 InitRotation(const Quaternion& rotation);
		static Matrix4 InitRotation(const Vector3& euler);
		static Matrix4 InitRotation(const Vector3& forward, const Vector3& right, const Vector3& up);
		static Matrix4 InitScale(const Vector3& scale);
		// Field of view is in radians
		static Matrix4 InitPerspectiveProjection(float fov, float ar, float zNear, float zFar);
		static Matrix4 InitPerspectiveProjection(float left, float right, float top, float bottom, float zNear, float zFar);

		Matrix4& Translate(float x, float y, float z);   // translation by (x,y,z)
		Matrix4& Translate(const Vector3& v);            //
		Matrix4& Rotate(float angle, const Vector3& axis); // rotate angle(degree) along the given axix
		Matrix4& Rotate(float angle, float x, float y, float z);
		Matrix4& RotateX(float angle);                   // rotate on X-axis with degree
		Matrix4& RotateY(float angle);                   // rotate on Y-axis with degree
		Matrix4& RotateZ(float angle);                   // rotate on Z-axis with degree
		Matrix4& Scale(float scale);                     // uniform scale
		Matrix4& Scale(float sx, float sy, float sz);    // scale by (sx, sy, sz) on each axis
		Matrix4& LookAt(float tx, float ty, float tz);   // face object to the target direction
		Matrix4& LookAt(float tx, float ty, float tz, float ux, float uy, float uz);
		Matrix4& LookAt(const Vector3& target);
		Matrix4& LookAt(const Vector3& target, const Vector3& up);

		Matrix4 operator+(const Matrix4& rhs) const;    // add rhs
		Matrix4 operator-(const Matrix4& rhs) const;    // subtract rhs
		Matrix4& operator+=(const Matrix4& rhs);         // add rhs and update this object
		Matrix4& operator-=(const Matrix4& rhs);         // subtract rhs and update this object
		Vector3 operator*(const Vector3& rhs) const;    // multiplication: v' = M * v
		Matrix4 operator*(const Matrix4& rhs) const;    // multiplication: M3 = M1 * M2
		Matrix4& operator*=(const Matrix4& rhs);         // multiplication: M1' = M1 * M2
		bool operator==(const Matrix4& rhs) const;   // exact compare, no epsilon
		bool operator!=(const Matrix4& rhs) const;   // exact compare, no epsilon
		float operator[](int index) const;            // subscript operator v[0], v[1]
		float& operator[](int index);                  // subscript operator v[0], v[1]
	};
}