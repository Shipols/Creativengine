#pragma once

#include <string>

namespace Creativengine {

	struct ShaderProgarmSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	private:
		std::string m_FilePath;
		unsigned int m_RenderID;
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		// Uniforms
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	private:
		ShaderProgarmSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		
		unsigned int GetUniformLocaion(const std::string& name);
	};

}