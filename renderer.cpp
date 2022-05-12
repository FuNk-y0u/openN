#include "renderer.h"
#include <GL/glew.h>
#include<iostream>
#include<stdio.h>

//clears error 
void GLClearError()
{
	while(glGetError() != GL_NO_ERROR);
}

//error printing stuff
bool GlLogCall(const char* function, const char* file, int line)
{
	while(GLenum error = glGetError())
	{
		printf("%x\n", error);
		std::cout << "[ERROR OPENGL]: " << error << "## on f(x): " << function << "## FILE: " << file << "## on line: " << line << std::endl;
		return false;
	}
	return true;
}
