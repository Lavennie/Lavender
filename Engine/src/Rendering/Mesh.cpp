#include <windows.h>
#include <memory>
#include <GL/gl.h>
#include <GL/GLEXT.h>
#include "Logging/Logging.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include <iostream>
#include <fstream>

#include "Mesh.h"

namespace Lavender
{
	Mesh::Mesh() : m_Vao(0), m_Vbo(0), m_Ibo(0), m_IndexCount(0) {}
	Mesh::Mesh(const string& path) : Mesh()
	{
		/*MESH FORMAT
		* vertex count (uint64)
		* vertices: position (vec3 float4), tex coord (vec2 float4), normal (vec3 float4)
		* index count (uint64)
		* indices: uint32
		*/
		ifstream file(path, ios::binary | ios::in);

		if (!file.is_open())
		{
			Log::Print("Failed to open mesh at path " + path, Log::Level::LevelError);
			file.close();
			return;
		}

		UINT64 vertexCount;
		file.read((char*)&vertexCount, 8);
		Vertex* vertices = new Vertex[vertexCount];
		for (size_t i = 0; i < vertexCount; i++)
		{
			file.read((char*)&vertices[i].position.x, 4);
			file.read((char*)&vertices[i].position.y, 4);
			file.read((char*)&vertices[i].position.z, 4);

			file.read((char*)&vertices[i].texCoord.x, 4);
			file.read((char*)&vertices[i].texCoord.y, 4);

			file.read((char*)&vertices[i].normal.x, 4);
			file.read((char*)&vertices[i].normal.y, 4);
			file.read((char*)&vertices[i].normal.z, 4);

			Log::Print(vertices[i].position);
		}

		UINT64 indexCount;
		file.read((char*)&indexCount, 8);
		indexCount *= 3;
		unsigned int* indices = new unsigned int[indexCount];
		for (size_t i = 0; i < indexCount; i++)
		{
			file.read((char*)&indices[i], 4);
		}

		file.close();

		VertexAttribPointer attribs[3]
		{
			VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)),
			VertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord)),
			VertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal))
		};

		InitMesh((size_t)vertexCount, vertices, (size_t)indexCount, indices, 3, attribs);

		delete[] vertices;
		delete[] indices;
	}
	Mesh::Mesh(Mesh&& source) : m_Vao{ source.m_Vao }, m_Vbo{ source.m_Vbo }, m_Ibo{ source.m_Ibo }, m_IndexCount{ source.m_IndexCount }
	{
		source.m_Vbo = 0;
	}
	Mesh::~Mesh()
	{
		if (m_Vbo != 0)
		{
			((PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays"))(1, &m_Vao);
			((PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers"))(1, &m_Vbo);
			((PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers"))(1, &m_Ibo);
			Log::Print("Deleted mesh");
		}
	}

	void Mesh::InitMesh(size_t vertexCount, const Vertex* vertices, size_t indexCount, const unsigned int* indices, size_t attribCount, const VertexAttribPointer* attribs)
	{
		m_IndexCount = indexCount;

		((PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays"))(1, &m_Vao);
		((PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers"))(1, &m_Vbo);
		((PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers"))(1, &m_Ibo);

		((PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray"))(m_Vao);

		((PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer"))(GL_ARRAY_BUFFER, m_Vbo);
		((PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData"))(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

		((PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer"))(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
		((PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData"))(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		for (size_t i = 0; i < attribCount; i++)
		{
			((PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray"))(attribs[i].index);
			((PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer"))
				(attribs[i].index, attribs[i].size, attribs[i].type, attribs[i].normalized, attribs[i].stride, attribs[i].offset);
		}
	}

    void Mesh::Draw() const
    {
		// bind buffers
		((PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray"))(m_Vao);
		((PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer"))(GL_ARRAY_BUFFER, m_Vbo);
		((PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer"))(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
		// draw mesh
		((PFNGLDRAWELEMENTSBASEVERTEXPROC)wglGetProcAddress("glDrawElementsBaseVertex"))(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0, 0);
    }

	unsigned int Mesh::GetVbo() const
	{
		return m_Vbo;
	}
}