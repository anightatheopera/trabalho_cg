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

class Scene {

    public:
    Camera camera;
    Group group;

    Scene(Camera camera, Group group);
    Scene();

    auto render(bool picker = false,bool lines = false) -> void;
    auto load_models() -> void;
    auto vbo__init__() -> void;
};

#endif
