#include "ShaderDatabase.h"
#include <fstream>
#include "Logging/Logging.h"
#include "Core.h"

namespace Lavender
{
	ShaderDatabase::ShaderDatabase()
	{
		Log::PrintInfo("Created Shader Database");
	}
	ShaderDatabase::~ShaderDatabase()
	{
		Log::PrintInfo("Deleted Shader Database");
	}
	ShaderDatabase& ShaderDatabase::Instance() { return Core::GetInstance()->GetShaders(); }

	Shader* ShaderDatabase::GetShader(const string& vertexShaderPath, const string& fragmentShaderPath)
	{
		map<pair<string, string>, unsigned int>::iterator it = Instance().m_FileShaders.find(pair<string, string>(vertexShaderPath, fragmentShaderPath));
		if (it != Instance().m_FileShaders.end())
		{
			return GetShader(it->second);
		}
		return nullptr;
	}
	Shader* ShaderDatabase::GetShader(unsigned int shaderProgram)
	{
		for (Shader& shader : Instance().m_Shaders)
		{
			if (shader.GetProgramId() == shaderProgram)
			{
				return &shader;
			}
		}
		return nullptr;
	}

	Shader* ShaderDatabase::LoadShader(const string& vertexSourcePath, const string& fragmentSourcePath)
	{
		ifstream fileVert(vertexSourcePath, ios::in);
		ifstream fileFrag(fragmentSourcePath, ios::in);
		if (!fileVert.is_open() || !fileFrag.is_open()) 
		{ 
			fileVert.close();
			fileFrag.close();
			return nullptr; 
		}
		fileVert.close();
		fileFrag.close();

		// return an already loaded mesh
		Shader* shader = GetShader(vertexSourcePath, fragmentSourcePath);
		if (shader != nullptr) { return shader; }
		// load mesh anew
		Instance().m_Shaders.emplace_back(vertexSourcePath, fragmentSourcePath);
		Instance().m_FileShaders.emplace(pair<string, string>(vertexSourcePath, fragmentSourcePath), Instance().m_Shaders.back().GetProgramId());
		return &Instance().m_Shaders.back();
	}
}