#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <string>
#include <map>
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Matrix4.h"

using namespace std;

namespace Lavender
{
	class Shader
	{
	private:
		unsigned int m_Id;
		map<string, GLint> m_Uniforms;
	public:
		Shader();
		~Shader();

		void InitShader(const string& vertexSource, const string& fragmentSource);
		void InitShaderFromFile(const string& vertexSourcePath, const string& fragmentSourcePath);

		void Bind() const;
		void Unbind() const;

		void SetUniform(const string name, float value) const;
		void SetUniform(const string name, const Vector2& value) const;
		void SetUniform(const string name, const Vector3& value) const;
		void SetUniform(const string name, int value) const;
		void SetUniform(const string name, unsigned int value) const;
		void SetUniform(const string name, const Matrix4& value) const;
	};
}