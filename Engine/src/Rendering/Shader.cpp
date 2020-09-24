#include "Shader.h"
#include <GL/GLEXT.h>
#include "Logging/Logging.h"

using namespace std;

namespace Lavender
{
	Shader::Shader() : m_Id(-1), m_Uniforms(map<string, GLint>()) {}
	Shader::~Shader()
	{
		((PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram"))(m_Id);
		Log::PrintInfo("Deleted shader program");
	}

	void Shader::InitShader(const string& vertexSource, const string& fragmentSource)
	{
		// vertex shader
		unsigned int vertexShader = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))(GL_VERTEX_SHADER);
		const char* vSource = vertexSource.c_str();
		((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(vertexShader, 1, &vSource, NULL);
		((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(vertexShader);
		// check for compile errors
		GLint success;
		((PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv"))(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			((PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog"))(vertexShader, 512, NULL, infoLog);
			Log::PrintError("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
			Log::PrintError(infoLog);
		}

		// fragment shader
		unsigned int fragmentShader = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))(GL_FRAGMENT_SHADER);
		const char* fSource = fragmentSource.c_str();
		((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(fragmentShader, 1, &fSource, NULL);
		((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(fragmentShader);
		// check for compile errors
		((PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv"))(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			((PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog"))(fragmentShader, 512, NULL, infoLog);
			Log::PrintError("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
			Log::PrintError(infoLog);
		}


		// shader program
		m_Id = ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram"))();
		// attach vertex and fragment shader
		((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(m_Id, vertexShader);
		((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(m_Id, fragmentShader);
		((PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram"))(m_Id);
		// check for link errors
		((PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv"))(m_Id, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			((PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog"))(m_Id, 512, NULL, infoLog);
			Log::PrintError("ERROR::SHADER::LINK_FAILED");
			Log::PrintError(infoLog);
		}

		((PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader"))(vertexShader);
		((PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader"))(fragmentShader);


		// save uniform locations
		GLint count;
		((PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv"))(m_Id, GL_ACTIVE_UNIFORMS, &count);

		GLsizei length;
		GLint size;
		GLenum type;
		GLchar name[16];
		GLint location;
		for (int i = 0; i < count; i++)
		{
			((PFNGLGETACTIVEUNIFORMPROC)wglGetProcAddress("glGetActiveUniform"))(m_Id, (GLuint)i, 16, &length, &size, &type, name);
			location = ((PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation"))(m_Id, name);

			m_Uniforms.insert(std::pair<string, GLint>(name, location));
		}
	}

	void Shader::Bind() const
	{
		((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(m_Id);
	}
	void Shader::Unbind() const
	{
		((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(NULL);
	}

	void Shader::SetUniform(const string name, float value) const
	{
		GLint location = m_Uniforms.at(name);
		((PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f"))(m_Uniforms.at(name), value);
	}
	void Shader::SetUniform(const string name, const Vector2& value) const
	{
		((PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f"))(m_Uniforms.at(name), value.x, value.y);
	}
	void Shader::SetUniform(const string name, const Vector3& value) const
	{
		((PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f"))(m_Uniforms.at(name), value.x, value.y, value.z);
	}
	void Shader::SetUniform(const string name, int value) const
	{
		((PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i"))(m_Uniforms.at(name), value);
	}
	void Shader::SetUniform(const string name, unsigned int value) const
	{
		((PFNGLUNIFORM1UIPROC)wglGetProcAddress("glUniform1ui"))(m_Uniforms.at(name), value);
	}
	void Shader::SetUniform(const string name, Matrix4& value) const
	{
		((PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv"))(m_Uniforms.at(name), 1, GL_FALSE, &value[0]);
	}
}