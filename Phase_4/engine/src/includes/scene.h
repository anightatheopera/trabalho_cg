//Purpose: Header file for scene.cpp
#ifndef SCENE_H
#define SCENE_H


#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <string>

#include "points.h"
#include "group.h"
#include "camera.h"
#include "light.h"

class Scene {

    public:
    vector<Light> lights;
    Camera camera;
    Group group;

    Scene(Camera camera, Group group, vector<Light> lights);
    Scene();

    auto render(bool picker = false,bool lines = false) -> void;
    auto vbo__init__() -> void;
    auto __init__() -> void;
};

#endif
