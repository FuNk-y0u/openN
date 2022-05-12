linux:
	g++ -c *.cpp
	g++ -o openN openN.o indexbuffer.o vertexbuffer.o renderer.o vertexarray.o shader.o -lGLEW -lSDL2 -lGL -lGLU -lglut
