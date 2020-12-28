#define _USE_MATH_DEFINES
#include <cmath>
#include "Matrix4.h"

namespace Lavender
{
	const float DEG2RAD = 3.141593f / 180.0f;
	const float RAD2DEG = 180.0f / 3.141593f;
	const float EPSILON = 0.00001f;

	Matrix4::Matrix4()
	{
		Identity();
	}
	Matrix4::Matrix4(const float src[16])
	{
		Set(src);
	}
	Matrix4::Matrix4(float m00, float m01, float m02, float m03,
		float m04, float m05, float m06, float m07,
		float m08, float m09, float m10, float m11,
		float m12, float m13, float m14, float m15)
	{
		Set(m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15);
	}

	void Matrix4::Set(const float src[16])
	{
		m[0] = src[0];  m[1] = src[1];  m[2] = src[2];  m[3] = src[3];
		m[4] = src[4];  m[5] = src[5];  m[6] = src[6];  m[7] = src[7];
		m[8] = src[8];  m[9] = src[9];  m[10] = src[10]; m[11] = src[11];
		m[12] = src[12]; m[13] = src[13]; m[14] = src[14]; m[15] = src[15];
	}
	void Matrix4::Set(float m00, float m01, float m02, float m03,
		float m04, float m05, float m06, float m07,
		float m08, float m09, float m10, float m11,
		float m12, float m13, float m14, float m15)
	{

		m[0] = m00;  m[1] = m01;  m[2] = m02;  m[3] = m03;
		m[4] = m04;  m[5] = m05;  m[6] = m06;  m[7] = m07;
		m[8] = m08;  m[9] = m09;  m[10] = m10;  m[11] = m11;
		m[12] = m12;  m[13] = m13;  m[14] = m14;  m[15] = m15;
	}

	void Matrix4::SetRow(int index, const float row[4])
	{
		m[index] = row[0];
		m[index + 4] = row[1];
		m[index + 8] = row[2];
		m[index + 12] = row[3];
	}
	void Matrix4::SetRow(int index, const Vector3& v)
	{
		m[index] = v.x;  m[index + 4] = v.y;  m[index + 8] = v.z;
	}
	void Matrix4::SetColumn(int index, const float col[4])
	{
		m[index * 4] = col[0];
		m[index * 4 + 1] = col[1];
		m[index * 4 + 2] = col[2];
		m[index * 4 + 3] = col[3];
	}
	void Matrix4::SetColumn(int index, const Vector3& v)
	{
		m[index * 4] = v.x;  m[index * 4 + 1] = v.y;  m[index * 4 + 2] = v.z;
	}

	const float* Matrix4::Get() const
	{
		return m;
	}
	const void Matrix4::GetTranspose(float* tm)
	{
		tm[0] = m[0];   tm[1] = m[4];   tm[2] = m[8];   tm[3] = m[12];
		tm[4] = m[1];   tm[5] = m[5];   tm[6] = m[9];   tm[7] = m[13];
		tm[8] = m[2];   tm[9] = m[6];   tm[10] = m[10];  tm[11] = m[14];
		tm[12] = m[3];   tm[13] = m[7];   tm[14] = m[11];  tm[15] = m[15];
	}

	Matrix4& Matrix4::Identity()
	{
		m[0] = m[5] = m[10] = m[15] = 1.0f;
		m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
		return *this;
	}
	Matrix4& Matrix4::Transpose()
	{
		float temp = m[1];
		m[1] = m[4]; m[4] = temp;
		temp = m[2];
		m[2] = m[8]; m[8] = temp;
		temp = m[3];
		m[3] = m[12]; m[12] = temp;
		temp = m[6];
		m[6] = m[9]; m[9] = temp;
		temp = m[7];
		m[7] = m[13]; m[13] = temp;
		temp = m[11];
		m[11] = m[14]; m[14] = temp;

		return *this;
	}

	Matrix4 Matrix4::InitTranslation(const Vector3& translation)
	{
		// translation x, y and z are at 12, 13 and 14 indices respectively
		return Matrix4(
			1,			   0,			  0,			 0,
			0,			   1,			  0,			 0,
			0,			   0,			  1,			 0,
			translation.x, translation.y, translation.z, 1);
	}
	Matrix4 Matrix4::InitRotation(const Quaternion& rotation)
	{
		const Quaternion& q = rotation;
		return Matrix4(
			1.0f - 2.0f * q.v.y * q.v.y - 2.0f * q.v.z * q.v.z, 2.0f * q.v.x * q.v.y + 2.0f * q.w * q.v.z,			2.0f * q.v.x * q.v.z - 2.0f * q.w * q.v.y,			0,
			2.0f * q.v.x * q.v.y - 2.0f * q.v.z * q.w,			1.0f - 2.0f * q.v.x * q.v.x - 2.0f * q.v.z * q.v.z, 2.0f * q.v.y * q.v.z + 2.0f * q.w * q.v.x,			0,
			2.0f * q.v.x * q.v.z + 2.0f * q.v.y * q.w,			2.0f * q.v.z * q.v.y - 2.0f * q.v.x * q.w,			1.0f - 2.0f * q.v.x * q.v.x - 2.0f * q.v.y * q.v.y, 0,
			0,													0,													0,													1.0f);
	}
	Matrix4 Matrix4::InitRotation(const Vector3& euler)
	{
		float cx = cos(euler.x * (M_PI / 180.0f));
		float sx = sin(euler.x * (M_PI / 180.0f));
		float cy = cos(euler.y * (M_PI / 180.0f));
		float sy = sin(euler.y * (M_PI / 180.0f));
		float cz = cos(euler.z * (M_PI / 180.0f));
		float sz = sin(euler.z * (M_PI / 180.0f));

		Matrix4 rx = Matrix4(
			1, 0,   0,  0, 
			0, cx,  sx, 0,
			0, -sx, cx, 0,
			0, 0,   0,  1);
		Matrix4 ry = Matrix4(
			cy, 0, -sy, 0,
			0,  1, 0,   0,
			sy, 0, cy,  0,
			0,  0, 0,   1);
		Matrix4 rz = Matrix4(
			cz,  sz, 0, 0,
			-sz, cz, 0, 0,
			0,   0,  1, 0,
			0,   0,  0, 1);

		// YXZ axis order
		return rz * rx * ry;
	}
	Matrix4 Matrix4::InitRotation(const Vector3& forward, const Vector3& right, const Vector3& up)
	{
		return Matrix4(
			right.x,   right.y,   right.z,	 0,
			up.x,	   up.y,	  up.z,		 0,
			forward.x, forward.y, forward.z, 0,
			0,		   0,		  0,		 1);
	}
	Matrix4 Matrix4::InitScale(const Vector3& scale)
	{
		return Matrix4(
			scale.x, 0,		  0,	   0,
			0,		 scale.y, 0,	   0,
			0,		 0,		  scale.z, 0,
			0,		 0,		  0,	   1);
	}
	Matrix4 Matrix4::InitPerspectiveProjection(float fov, float ar, float zNear, float zFar) 
	{
		return Matrix4(
			1.0f / (ar * tan(fov / 2.0f)), 0,					   0,									   0,
			0,							   1.0f / tan(fov / 2.0f), 0,									   0,
			0,							   0,					   (-zFar - zNear) / (zNear - zFar),	   1.0f,
			0,							   0,					   (2.0f * zFar * zNear) / (zNear - zFar), 0);
	}
	Matrix4 Matrix4::InitPerspectiveProjection(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		return Matrix4(
			(2.0f * zNear) / (right - left), 0,								  (right + left) / (right - left),	0,
			0,								 (2.0f * zNear) / (top - bottom), (top + bottom) / (top - bottom),	0,
			0,								 0,								  -(zFar + zNear) / (zFar - zNear), (-2.0f * zFar * zNear) / (zFar - zNear),
			0,								 0,								  -1.0f,							0);
	}
	Matrix4 Matrix4::InitOrthographicProjection(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		return Matrix4(
			2.0f / (right - left), 0, 0, 0,
			0, 2.0f / tan(top - bottom), 0, 0,
			0, 0, -2.0f / (zFar - zNear), 0,
			-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(zFar + zNear) / (zFar - zNear), 1.0f);
	}

	Matrix4& Matrix4::Translate(float x, float y, float z)
	{
		m[0] += m[3] * x;   m[4] += m[7] * x;   m[8] += m[11] * x;   m[12] += m[15] * x;
		m[1] += m[3] * y;   m[5] += m[7] * y;   m[9] += m[11] * y;   m[13] += m[15] * y;
		m[2] += m[3] * z;   m[6] += m[7] * z;   m[10] += m[11] * z;   m[14] += m[15] * z;

		return *this;
	}
	Matrix4& Matrix4::Translate(const Vector3& v)
	{
		return Translate(v.x, v.y, v.z);
	}

	Matrix4& Matrix4::Rotate(float angle, const Vector3& axis)
	{
		return Rotate(angle, axis.x, axis.y, axis.z);
	}
	Matrix4& Matrix4::Rotate(float angle, float x, float y, float z)
	{
		float c = cosf(angle * DEG2RAD);    // cosine
		float s = sinf(angle * DEG2RAD);    // sine
		float c1 = 1.0f - c;                // 1 - c
		float m0 = m[0], m4 = m[4], m8 = m[8], m12 = m[12],
			m1 = m[1], m5 = m[5], m9 = m[9], m13 = m[13],
			m2 = m[2], m6 = m[6], m10 = m[10], m14 = m[14];

		// build rotation matrix
		float r0 = x * x * c1 + c;
		float r1 = x * y * c1 + z * s;
		float r2 = x * z * c1 - y * s;
		float r4 = x * y * c1 - z * s;
		float r5 = y * y * c1 + c;
		float r6 = y * z * c1 + x * s;
		float r8 = x * z * c1 + y * s;
		float r9 = y * z * c1 - x * s;
		float r10 = z * z * c1 + c;

		// multiply rotation matrix
		m[0] = r0 * m0 + r4 * m1 + r8 * m2;
		m[1] = r1 * m0 + r5 * m1 + r9 * m2;
		m[2] = r2 * m0 + r6 * m1 + r10 * m2;
		m[4] = r0 * m4 + r4 * m5 + r8 * m6;
		m[5] = r1 * m4 + r5 * m5 + r9 * m6;
		m[6] = r2 * m4 + r6 * m5 + r10 * m6;
		m[8] = r0 * m8 + r4 * m9 + r8 * m10;
		m[9] = r1 * m8 + r5 * m9 + r9 * m10;
		m[10] = r2 * m8 + r6 * m9 + r10 * m10;
		m[12] = r0 * m12 + r4 * m13 + r8 * m14;
		m[13] = r1 * m12 + r5 * m13 + r9 * m14;
		m[14] = r2 * m12 + r6 * m13 + r10 * m14;

		return *this;
	}
	Matrix4& Matrix4::RotateX(float angle)
	{
		float c = cosf(angle * DEG2RAD);
		float s = sinf(angle * DEG2RAD);
		float m1 = m[1], m2 = m[2],
			m5 = m[5], m6 = m[6],
			m9 = m[9], m10 = m[10],
			m13 = m[13], m14 = m[14];

		m[1] = m1 * c + m2 * -s;
		m[2] = m1 * s + m2 * c;
		m[5] = m5 * c + m6 * -s;
		m[6] = m5 * s + m6 * c;
		m[9] = m9 * c + m10 * -s;
		m[10] = m9 * s + m10 * c;
		m[13] = m13 * c + m14 * -s;
		m[14] = m13 * s + m14 * c;

		return *this;
	}
	Matrix4& Matrix4::RotateY(float angle)
	{
		float c = cosf(angle * DEG2RAD);
		float s = sinf(angle * DEG2RAD);
		float m0 = m[0], m2 = m[2],
			m4 = m[4], m6 = m[6],
			m8 = m[8], m10 = m[10],
			m12 = m[12], m14 = m[14];

		m[0] = m0 * c + m2 * s;
		m[2] = m0 * -s + m2 * c;
		m[4] = m4 * c + m6 * s;
		m[6] = m4 * -s + m6 * c;
		m[8] = m8 * c + m10 * s;
		m[10] = m8 * -s + m10 * c;
		m[12] = m12 * c + m14 * s;
		m[14] = m12 * -s + m14 * c;

		return *this;
	}
	Matrix4& Matrix4::RotateZ(float angle)
	{
		float c = cosf(angle * DEG2RAD);
		float s = sinf(angle * DEG2RAD);
		float m0 = m[0], m1 = m[1],
			m4 = m[4], m5 = m[5],
			m8 = m[8], m9 = m[9],
			m12 = m[12], m13 = m[13];

		m[0] = m0 * c + m1 * -s;
		m[1] = m0 * s + m1 * c;
		m[4] = m4 * c + m5 * -s;
		m[5] = m4 * s + m5 * c;
		m[8] = m8 * c + m9 * -s;
		m[9] = m8 * s + m9 * c;
		m[12] = m12 * c + m13 * -s;
		m[13] = m12 * s + m13 * c;

		return *this;
	}

	Matrix4& Matrix4::Scale(float s)
	{
		return Scale(s, s, s);
	}
	Matrix4& Matrix4::Scale(float x, float y, float z)
	{
		m[0] *= x;   m[4] *= x;   m[8] *= x;   m[12] *= x;
		m[1] *= y;   m[5] *= y;   m[9] *= y;   m[13] *= y;
		m[2] *= z;   m[6] *= z;   m[10] *= z;   m[14] *= z;
		return *this;
	}

	Matrix4& Matrix4::LookAt(const Vector3& target)
	{
		// compute forward vector and normalize
		Vector3 position = Vector3(m[12], m[13], m[14]);
		Vector3 forward = target - position;
		forward.Normalize();
		Vector3 up;             // up vector of object
		Vector3 left;           // left vector of object

		// compute temporal up vector
		// if forward vector is near Y-axis, use up vector (0,0,-1) or (0,0,1)
		if (fabs(forward.x) < EPSILON && fabs(forward.z) < EPSILON)
		{
			// forward vector is pointing +Y axis
			if (forward.y > 0)
				up.Set(0, 0, -1);
			// forward vector is pointing -Y axis
			else
				up.Set(0, 0, 1);
		}
		else
		{
			// assume up vector is +Y axis
			up.Set(0, 1, 0);
		}

		// compute left vector
		left = up.Cross(forward);
		left.Normalize();

		// re-compute up vector
		up = forward.Cross(left);
		//up.normalize();

		// NOTE: overwrite rotation and scale info of the current matrix
		this->SetColumn(0, left);
		this->SetColumn(1, up);
		this->SetColumn(2, forward);

		return *this;
	}
	Matrix4& Matrix4::LookAt(const Vector3& target, const Vector3& upVec)
	{
		// compute forward vector and normalize
		Vector3 position = Vector3(m[12], m[13], m[14]);
		Vector3 forward = target - position;
		forward.Normalize();

		// compute left vector
		Vector3 left = upVec.Cross(forward);
		left.Normalize();

		// compute orthonormal up vector
		Vector3 up = forward.Cross(left);
		up.Normalize();

		// NOTE: overwrite rotation and scale info of the current matrix
		this->SetColumn(0, left);
		this->SetColumn(1, up);
		this->SetColumn(2, forward);

		return *this;
	}
	Matrix4& Matrix4::LookAt(float tx, float ty, float tz)
	{
		return LookAt(Vector3(tx, ty, tz));
	}
	Matrix4& Matrix4::LookAt(float tx, float ty, float tz, float ux, float uy, float uz)
	{
		return LookAt(Vector3(tx, ty, tz), Vector3(ux, uy, uz));
	}

	Matrix4 Matrix4::operator+(const Matrix4& rhs) const
	{
		return Matrix4(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3],
			m[4] + rhs[4], m[5] + rhs[5], m[6] + rhs[6], m[7] + rhs[7],
			m[8] + rhs[8], m[9] + rhs[9], m[10] + rhs[10], m[11] + rhs[11],
			m[12] + rhs[12], m[13] + rhs[13], m[14] + rhs[14], m[15] + rhs[15]);
	}
	Matrix4 Matrix4::operator-(const Matrix4& rhs) const
	{
		return Matrix4(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3],
			m[4] - rhs[4], m[5] - rhs[5], m[6] - rhs[6], m[7] - rhs[7],
			m[8] - rhs[8], m[9] - rhs[9], m[10] - rhs[10], m[11] - rhs[11],
			m[12] - rhs[12], m[13] - rhs[13], m[14] - rhs[14], m[15] - rhs[15]);
	}
	Matrix4& Matrix4::operator+=(const Matrix4& rhs)
	{
		m[0] += rhs[0];   m[1] += rhs[1];   m[2] += rhs[2];   m[3] += rhs[3];
		m[4] += rhs[4];   m[5] += rhs[5];   m[6] += rhs[6];   m[7] += rhs[7];
		m[8] += rhs[8];   m[9] += rhs[9];   m[10] += rhs[10];  m[11] += rhs[11];
		m[12] += rhs[12];  m[13] += rhs[13];  m[14] += rhs[14];  m[15] += rhs[15];
		return *this;
	}
	Matrix4& Matrix4::operator-=(const Matrix4& rhs)
	{
		m[0] -= rhs[0];   m[1] -= rhs[1];   m[2] -= rhs[2];   m[3] -= rhs[3];
		m[4] -= rhs[4];   m[5] -= rhs[5];   m[6] -= rhs[6];   m[7] -= rhs[7];
		m[8] -= rhs[8];   m[9] -= rhs[9];   m[10] -= rhs[10];  m[11] -= rhs[11];
		m[12] -= rhs[12];  m[13] -= rhs[13];  m[14] -= rhs[14];  m[15] -= rhs[15];
		return *this;
	}
	Vector3 Matrix4::operator*(const Vector3& rhs) const
	{
		return Vector3(m[0] * rhs.x + m[1] * rhs.y + m[2] * rhs.z + m[3],
			m[4] * rhs.x + m[5] * rhs.y + m[6] * rhs.z + m[7],
			m[8] * rhs.x + m[9] * rhs.y + m[10] * rhs.z + m[11]);
	}
	Matrix4 Matrix4::operator*(const Matrix4& n) const
	{
		/*return Matrix4(
			m[0]  *	n[0] + m[1]  * n[4] + m[2]  * n[8] + m[3]  * n[12],		m[0]  * n[1] + m[1]  * n[5] + m[2]	* n[9] + m[3]  * n[13],		m[0]  * n[2] + m[1]  * n[6] + m[2]  * n[10] + m[3]  * n[14],	m[0]  * n[3] + m[1]  * n[7] + m[2]  * n[11] + m[3]  * n[15],
			m[4]  *	n[0] + m[5]  * n[4] + m[6]  * n[8] + m[7]  * n[12],		m[4]  * n[1] + m[5]  * n[5] + m[6]	* n[9] + m[7]  * n[13],		m[4]  * n[2] + m[5]  * n[6] + m[6]  * n[10] + m[7]  * n[14],	m[4]  * n[3] + m[5]  * n[7] + m[6]  * n[11] + m[7]  * n[15],
			m[8]  *	n[0] + m[9]  * n[4] + m[10] * n[8] + m[11] * n[12],		m[8]  * n[1] + m[9]  * n[5] + m[10] * n[9] + m[11] * n[13],		m[8]  * n[2] + m[9]  * n[6] + m[10] * n[10] + m[11] * n[14],	m[8]  * n[3] + m[9]  * n[7] + m[10] * n[11] + m[11] * n[15],
			m[12] * n[0] + m[13] * n[4] + m[14] * n[8] + m[15] * n[12],		m[12] * n[1] + m[13] * n[5] + m[14] * n[9] + m[15] * n[13],		m[12] * n[2] + m[13] * n[6] + m[14] * n[10] + m[15] * n[14],	m[12] * n[3] + m[13] * n[7] + m[14] * n[11] + m[15] * n[15]
		);*/
		return Matrix4(
			m[0] * n[0]  + m[4] * n[1]  + m[8] * n[2]  + m[12] * n[3],		m[1] * n[0]  + m[5] * n[1]  + m[9] * n[2]  + m[13] * n[3],		m[2] * n[0]  + m[6] * n[1]  + m[10] * n[2]  + m[14] * n[3],		m[3] * n[0]  + m[7] * n[1]  + m[11] * n[2]  + m[15] * n[3],
			m[0] * n[4]  + m[4] * n[5]  + m[8] * n[6]  + m[12] * n[7],		m[1] * n[4]  + m[5] * n[5]  + m[9] * n[6]  + m[13] * n[7],		m[2] * n[4]  + m[6] * n[5]  + m[10] * n[6]  + m[14] * n[7],		m[3] * n[4]  + m[7] * n[5]  + m[11] * n[6]  + m[15] * n[7],
			m[0] * n[8]  + m[4] * n[9]  + m[8] * n[10] + m[12] * n[11],		m[1] * n[8]  + m[5] * n[9]  + m[9] * n[10] + m[13] * n[11],		m[2] * n[8]  + m[6] * n[9]  + m[10] * n[10] + m[14] * n[11],	m[3] * n[8]  + m[7] * n[9]  + m[11] * n[10] + m[15] * n[11],
			m[0] * n[12] + m[4] * n[13] + m[8] * n[14] + m[12] * n[15],		m[1] * n[12] + m[5] * n[13] + m[9] * n[14] + m[13] * n[15],		m[2] * n[12] + m[6] * n[13] + m[10] * n[14] + m[14] * n[15],	m[3] * n[12] + m[7] * n[13] + m[11] * n[14] + m[15] * n[15]
		);
	}
	Matrix4& Matrix4::operator*=(const Matrix4& rhs)
	{
		*this = *this * rhs;
		return *this;
	}
	bool Matrix4::operator==(const Matrix4& n) const
	{
		return (m[0] == n[0]) && (m[1] == n[1]) && (m[2] == n[2]) && (m[3] == n[3]) &&
			(m[4] == n[4]) && (m[5] == n[5]) && (m[6] == n[6]) && (m[7] == n[7]) &&
			(m[8] == n[8]) && (m[9] == n[9]) && (m[10] == n[10]) && (m[11] == n[11]) &&
			(m[12] == n[12]) && (m[13] == n[13]) && (m[14] == n[14]) && (m[15] == n[15]);
	}
	bool Matrix4::operator!=(const Matrix4& n) const
	{
		return (m[0] != n[0]) || (m[1] != n[1]) || (m[2] != n[2]) || (m[3] != n[3]) ||
			(m[4] != n[4]) || (m[5] != n[5]) || (m[6] != n[6]) || (m[7] != n[7]) ||
			(m[8] != n[8]) || (m[9] != n[9]) || (m[10] != n[10]) || (m[11] != n[11]) ||
			(m[12] != n[12]) || (m[13] != n[13]) || (m[14] != n[14]) || (m[15] != n[15]);
	}
	float Matrix4::operator[](int index) const
	{
		return m[index];
	}
	float& Matrix4::operator[](int index)
	{
		return m[index];
	}
}