#pragma once
#include "Vertex.h"
#include "Rendering/VertexAttribPointer.h"

using namespace std;

namespace Lavender
{
	class Mesh
	{
	private:
		unsigned int m_Vao, m_Vbo, m_Ibo;
		unsigned int m_IndexCount;
	public:
		Mesh();
		~Mesh();

		void InitMesh(size_t vertexCount, const Vertex* vertices, size_t indexCount, const unsigned int* indices, size_t attribCount, const VertexAttribPointer* attribs);
		void InitMesh(const string& path);

		void Draw();
	};
}