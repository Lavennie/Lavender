#pragma once
#include <map>
#include <vector>
#include <string>
#include "Rendering/Shader.h"

namespace Lavender
{
	using namespace std;

	class ShaderDatabase
	{
	private:
		/// <summary>
		/// Shader programs mapped to file paths
		/// </summary>
		map<pair<string, string>, unsigned int> m_FileShaders;
		/// <summary>
		/// All loaded shaders
		/// </summary>
		vector<Shader> m_Shaders;

	private:
		static ShaderDatabase& Instance();
	public:
		ShaderDatabase();
		~ShaderDatabase();

		static Shader* GetShader(const string& vertexShaderPath, const string& fragmentShaderPath);
		static Shader* GetShader(unsigned int shaderProgram);

		static Shader* LoadShader(const string& vertexSourcePath, const string& fragmentSourcePath);
	};
}