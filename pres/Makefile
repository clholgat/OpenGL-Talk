all: example triangles

example: glut.o
	gcc -lGL -lglut -lGLU -std=c++0x glut.o -o example
	
glut.o: glut.cpp
	gcc -lGL -lglut -lGLU -std=c++0x glut.cpp -c
	
triangles: triangles.o
	gcc -lGL -lglut -lGLU -std=c++0x triangles.o -o triangles
	
triangles.o: triangles.cpp
	gcc -lGL -lglut -lGLU -std=c++0x triangles.cpp -c
