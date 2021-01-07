#include "MeshDatabase.h"
#include "Logging/Logging.h"
#include "Core.h"
#include <fstream>

namespace Lavender
{
	MeshDatabase::MeshDatabase()
	{
		Log::Print("Created Mesh Database");
	}
	MeshDatabase::~MeshDatabase()
	{
		Log::Print("Deleted Mesh Database");
	}

	MeshDatabase& MeshDatabase::Instance()
	{
		return Core::GetInstance()->m_Meshes;
	}

	Mesh* MeshDatabase::GetMesh(const string& meshPath)
	{
		map<string, unsigned int>::iterator it = Instance().m_FileMeshes.find(meshPath);
		if (it != Instance().m_FileMeshes.end())
		{
			return GetMesh(it->second);
		}
		return nullptr;
	}
	Mesh* MeshDatabase::GetMesh(unsigned int meshVbo)
	{
		for (pair<Mesh, bool>& pair : Instance().m_Meshes)
		{
			if (pair.first.GetVbo() == meshVbo)
			{
				return &pair.first;
			}
		}
		return nullptr;
	}

	Mesh* MeshDatabase::LoadMesh(const string& meshPath, bool original)
	{
		ifstream file(meshPath, ios::in);
		if (!file.is_open()) 
		{ 
			file.close();
			return nullptr; 
		}
		file.close();

		if (original)
		{
			// load mesh anew since it must not share the buffer even if mesh from same file has already been loaded
			Instance().m_Meshes.emplace_back(Mesh(meshPath), original);
			return &Instance().m_Meshes.back().first;
		}
		else
		{
			// return an already loaded mesh
			Mesh* mesh = GetMesh(meshPath);
			if (mesh != nullptr) { return mesh; }
			// load mesh anew
			Instance().m_Meshes.emplace_back(meshPath, original);
			Instance().m_FileMeshes.emplace(meshPath, Instance().m_Meshes.back().first.GetVbo());
			return &Instance().m_Meshes.back().first;
		}
	}
}