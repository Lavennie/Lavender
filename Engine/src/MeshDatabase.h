#pragma once
#include <map>
#include <memory>
#include <vector>
#include "Rendering/Mesh.h"

namespace Lavender
{
	using namespace std;

	class MeshDatabase
	{
	private:
		/// <summary>
		/// VBOs mapped to file paths
		/// </summary>
		map<string, unsigned int> m_FileMeshes;
		/// <summary>
		/// Meshes and boolean which teels if it is original (only 1 instance allowed)
		/// </summary>
		vector<pair<Mesh, bool>> m_Meshes;

	private:
		static MeshDatabase& Instance();
	public:
		MeshDatabase();
		~MeshDatabase();

		static Mesh* GetMesh(const string& meshPath);
		static Mesh* GetMesh(unsigned int meshVbo);

		static Mesh* LoadMesh(const string& meshPath, bool original);
	};
}

