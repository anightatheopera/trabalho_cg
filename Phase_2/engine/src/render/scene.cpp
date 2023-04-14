#ifdef __APPLE__
#include <GLUT/glut.h>
#else
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

auto Scene::render(bool picker) -> void {
    this->camera.update();
    this->group.render(picker);
    this->group.pprint();
}

auto Scene::load_models() -> void {
    this->group.load_models();
}
