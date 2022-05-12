#pragma once

#include<string>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};
class shader
{
	private:
		std::string m_filepath;
		unsigned int m_RendererID;
	public:
		shader(const std::string& filepath);
		~shader();
		void Bind() const;
		void Unbind() const;
		
		void setuniform(const std::string& name, float v0, float v1, float v2, float v3);
	
	private:
		ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		int getuniformlocation(const std::string& nane);
};

