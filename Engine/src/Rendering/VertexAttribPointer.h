#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/GLEXT.h>

namespace Lavender
{
	struct VertexAttribPointer
	{
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* offset;

		VertexAttribPointer();
		VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);
	};
}