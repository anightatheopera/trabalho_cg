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

Scene::Scene(Camera camera, Group group, vector<Light> lights){
    this->camera = camera;
    this->group = group;
    this->lights = lights;
}

Scene::Scene(){
    this->camera = Camera();
    this->group = Group();
    this->lights = vector<Light>();
}

auto Scene::render(bool picker,bool lines) -> void {
    for (auto light : this->lights){
        light.render();
    }
    this->camera.update();
    this->group.render(picker,lines);
}


auto Scene::vbo__init__() -> void {
    for (auto light : this->lights){
        light.on();
    }
    this->group.vbo__init__();
}

auto Scene::__init__() -> void {   
    light_enable(); 
    this->vbo__init__();
}
