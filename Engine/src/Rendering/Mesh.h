#pragma once
#include <string>
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
		/// <summary>
		/// Load Mesh from file. Please check for path validity before calling this.
		/// Do not load directly using this but via MeshDatabase
		/// </summary>
		/// <param name="path">Path to mesh</param>
		Mesh(const string& path);
		~Mesh();

		void InitMesh(size_t vertexCount, const Vertex* vertices, size_t indexCount, const unsigned int* indices, size_t attribCount, const VertexAttribPointer* attribs);

		void Draw() const;

		unsigned int GetVbo() const;
	};
}