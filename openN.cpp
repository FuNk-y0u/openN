/*
 ██████  ██████  ███████ ███    ██ ███    ██
██    ██ ██   ██ ██      ████   ██ ████   ██
██    ██ ██████  █████   ██ ██  ██ ██ ██  ██
██    ██ ██      ██      ██  ██ ██ ██  ██ ██
 ██████  ██      ███████ ██   ████ ██   ████
*/

#include<GL/glew.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<stdio.h>
#include<string.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"renderer.h"
#include"vertexbuffer.h"
#include"indexbuffer.h"
#include"vertexarray.h"
#include"shader.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

SDL_Window* window = NULL;
SDL_GLContext gContext;

unsigned int buffer;
unsigned int ibo;
unsigned int vao;

float r = 0.0f;
float g = 0.0f;
float b = 0.0f;

float increment = 0.05f;
int location;

bool initGL();
bool init()
{
	//Initializing SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf("%s", SDL_GetError());
		return false;
	}
	//Use openGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		
	window = SDL_CreateWindow("OpenN",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		printf("%s",SDL_GetError());
		return false;
	}
	
	gContext = SDL_GL_CreateContext(window);
	if(gContext == NULL)
	{
		printf("%s", SDL_GetError());
		return false;
	}
	
	if(SDL_GL_SetSwapInterval(1) < 0)
	{
		printf("%s\n",SDL_GetError());
		return false;
	}
	if( !initGL())
	{
		printf("Unable to initialize gl\n");
		return false;
	}
	return true;
	
}

bool initGL()
{
	if(glewInit() != GLEW_OK)
	{
		printf("Error Failed To init glew");
	}

	printf("OpenN OpenGl Ver : %s\n",glGetString(GL_VERSION));

	return true;
}

int main(int argc, char* args[])
{
	if(!init())
	{
		printf("[ERROR] Unable to init!\n");
	}
	float positions[] = 
	{
		-0.5f, -0.5f,//0
		0.5f, -0.5f,//1
		0.5f, 0.5f,//2
		-0.5f, 0.5f//3


	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	vertexarray va;
	vertexbuffer vb(positions, 4 * 2 * sizeof(float));
	
	vertexbufferlayout layout;
	layout.push_float(2);
	va.addbuffer(vb, layout);

	indexbuffer ib(indices, 6);
	

	shader shader("res/shaders/basic.shader");
	/*
	shader shader("res/shaders/basic.shader");
	shader.Bind();
	shader.setuniform("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	*/


	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	//shader.Unbind();

	bool running = true;

	SDL_Event e;

	while(running)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				running = false;
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Bind();
		shader.setuniform("u_Color", r, g, b, 1.0f);

		
		va.Bind();
		ib.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, nullptr));
		
		if(r > 1.0f)
		{
			increment = -0.005f;
		}
		else if(r < 0.0f){
			increment = 0.005f;
		}

		r += increment; 
		

		SDL_GL_SwapWindow(window);
	}
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
	
	return 0;

}
