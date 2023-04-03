#ifndef SCENE_H
#define SCENE_H

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

    auto render() -> void;
    auto load_models() -> void;
};

#endif