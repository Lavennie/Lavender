#include "VertexAttribPointer.h"

namespace Lavender
{

	VertexAttribPointer::VertexAttribPointer() : index(-1), size(0), type(GL_FLOAT), normalized(GL_FALSE), stride(0), offset(0) {};
	VertexAttribPointer::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) :
		index(index), size(size), type(type), normalized(normalized), stride(stride), offset(offset) {}
}