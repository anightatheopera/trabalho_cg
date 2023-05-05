//Purpose: Header file for colorf.cpp
#ifndef COLORF_H
#define COLORF_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Color {
	public:
  		float r;
  		float g;
  		float b;

		Color(float r, float g, float b);
		Color(string hex);
		Color();

		auto show() -> void;
		auto apply() -> void;
	

};

#endif
