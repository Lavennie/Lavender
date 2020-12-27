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
	Mesh::~Mesh()
	{
		((PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays"))(1, &m_Vao);
		((PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers"))(1, &m_Vbo);
		((PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers"))(1, &m_Ibo);
		Log::PrintInfo("Deleted mesh");
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
			((PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray"))(i);
			((PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer"))
				(attribs[i].index, attribs[i].size, attribs[i].type, attribs[i].normalized, attribs[i].stride, attribs[i].offset);
		}
	}
	void Mesh::InitMesh(const string& path)
	{
		ifstream file(path, ios::binary | ios::in);

		if (!file.is_open())
		{
			Log::PrintError("Failed to open file at path " + path);
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
			VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal))
		};

		InitMesh((size_t)vertexCount, vertices, (size_t)indexCount, indices, 3, attribs);

		delete[] vertices;
		delete[] indices;

		/*vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		vector<Vector3> temp_vertices;
		vector<Vector2> temp_uvs;
		vector<Vector3> temp_normals;

		FILE* file = fopen(path.c_str(), "r");
		if (file == NULL)
		{
			Log::PrintError("Failed to open file " + path);
			return;
		}

		while (TRUE)
		{
			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)  // End Of File
			{
				break;
			}
			// vertex position
			if (strcmp(lineHeader, "v") == 0)
			{
				Vector3 position;
				fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);
				temp_vertices.push_back(position);
			}
			// texture coordinate
			else if (strcmp(lineHeader, "vt") == 0)
			{
				Vector2 texCoord;
				fscanf(file, "%f %f\n", &texCoord.x, &texCoord.y);
				temp_uvs.push_back(texCoord);
			}
			// normals
			else if (strcmp(lineHeader, "vn") == 0)
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			// face, texcoordinate and normal indices
			else if (strcmp(lineHeader, "f") == 0)
			{
				string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9)
				{
					Log::PrintError("File can't be read by this simple parser : (Try exporting with other options)");
					return;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}

		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			Vector3 vertex = temp_vertices[vertexIndices[i] - 1];

		}*/
	}

    void Mesh::Draw()
    {
		// bind buffers
		((PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray"))(m_Vao);
		((PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer"))(GL_ARRAY_BUFFER, m_Vbo);
		((PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer"))(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
        // draw mesh
		((PFNGLDRAWELEMENTSBASEVERTEXPROC)wglGetProcAddress("glDrawElementsBaseVertex"))(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0, 0);
    }
}