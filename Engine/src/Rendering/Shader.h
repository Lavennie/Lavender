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
		/// <summary>
		/// Load shader program with vertex and fragment shaders. Please check for path validity before calling this.
		/// Do not load directly using this but via ShaderDatabase
		/// </summary>
		/// <param name="vertexSourcePath">Path to vertex shader</param>
		/// <param name="fragmentSourcePath">Path to fragment shader</param>
		Shader(const string& vertexSourcePath, const string& fragmentSourcePath);
		~Shader();

		void InitShader(const string& vertexSource, const string& fragmentSource);

		void Bind() const;
		void Unbind() const;

		void SetUniform(const string& name, float value) const;
		void SetUniform(const string& name, const Vector2& value) const;
		void SetUniform(const string& name, const Vector3& value) const;
		void SetUniform(const string& name, int value) const;
		void SetUniform(const string& name, unsigned int value) const;
		void SetUniform(const string& name, const Matrix4& value) const;

		unsigned int GetProgramId() const;
	};
}