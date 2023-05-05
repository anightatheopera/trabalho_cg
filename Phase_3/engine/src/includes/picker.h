//Purpose: Header file for picker.cpp
#ifndef PICKER_H
#define PICKER_H


#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <string>


#include "scene.h"
#include "camera.h"

using namespace std;

auto picking(int x, int y, Scene scene) -> unsigned char;
auto render_hover_text(const string& text, int x, int y, Camera camera) -> void;

#endif
