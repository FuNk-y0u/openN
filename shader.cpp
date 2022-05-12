#include "shader.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"renderer.h"


shader::shader(const std::string& filepath)
	:m_filepath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

}

shader::~shader()
{
	GLCall(glDeleteProgram(m_RendererID));	
}


ShaderProgramSource shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if(line.find("#shader") != std::string::npos)
		{
			if(line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;	
			}
			else if(line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}
unsigned int shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1,&src, nullptr);
	glCompileShader(id);
	
	int results;
	glGetShaderiv(id, GL_COMPILE_STATUS, &results);
	if (results == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		fprintf(stderr, "Failed to compile [%s shader]\n", (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"));
        	fprintf(stderr, "%s\n", message);
	}

	return id;
}
unsigned int shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	
	return program;
}
void shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));	
}

void shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void shader::setuniform(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(getuniformlocation(name), v0, v1, v2, v3));	
}

int shader::getuniformlocation(const std::string& name)
{
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if(location == -1)
	{
		std::cout << "warning unifrom " << name << "doesnt exist!" << std::endl;	
	}
	return location;
}
