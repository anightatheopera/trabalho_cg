#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "scene.h"

Scene::Scene(Camera camera, Group group){
    this->camera = camera;
    this->group = group;
}

Scene::Scene(){
    this->camera = Camera();
    this->group = Group();
}

auto Scene::render(bool picker,bool lines) -> void {
    this->camera.update();
    this->group.render(picker,lines);
}

auto Scene::vbo__init__() -> void {
    this->group.vbo__init__();
}

auto Scene::__init__() -> void {
    this->vbo__init__();
}
