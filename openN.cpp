/*
 ██████  ██████  ███████ ███    ██ ███    ██
██    ██ ██   ██ ██      ████   ██ ████   ██
██    ██ ██████  █████   ██ ██  ██ ██ ██  ██
██    ██ ██      ██      ██  ██ ██ ██  ██ ██
 ██████  ██      ███████ ██   ████ ██   ████
*/

#include<GL/glew.h>
#include<GL/glu.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<stdio.h>
#include<string.h>

#include<iostream>

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;


bool init();

bool initGL();

void render();

void close();

//window variable
SDL_Window* window = NULL;

//openGL context
SDL_GLContext gContext;

unsigned int buffer;

static unsigned int CompileShader(unsigned int type, const std::string& source)
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
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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
	
	if(SDL_GL_SetSwapInterval(1) <0)
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

	printf("running on : %s\n",glGetString(GL_VERSION));
	GLenum error = GL_NO_ERROR;

	//Initialize projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//check for error
	error = glGetError();
	if( error != GL_NO_ERROR)
	{
		printf("%s\n", gluErrorString(error));
		return false;
	}

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		printf("%s\n", gluErrorString(error));
		return false;
	}
	
	float positions[6] = 
	{
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f, 0.5f
	};
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER,buffer);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(float), positions, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2,0);

	std::string vertexShader = 
		"#version 120\n"
		//"layout(location = 0) in vec4 positions;\n"
		"void main()\n"
		"{\n"
		//"	gl_FrontColor = gl_Color;\n"
		"	gl_Position = ftransform();\n"
		"}\n";

	
	std::string fragmentShader = 
		"#version 120\n"
		//"layout(location = 0) out vec4 color;"
		"void main(void)\n"
		"{\n"
		"	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";
	
	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);




	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	return true;
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void close()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

int main(int argc, char* args[])
{
	if(!init())
	{
		printf("Failed To init!");
		return -1;
	}

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
		render();

		SDL_GL_SwapWindow(window);
	}
	close();
	return 0;

}
