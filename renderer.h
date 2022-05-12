#pragma once
#include<GL/glew.h>

//error checking stuff
#define ASSERT(x) if (!(x))	  __asm__ volatile("int $0x03");
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GlLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GlLogCall(const char* function, const char* file, int line);
