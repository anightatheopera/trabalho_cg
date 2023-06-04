#ifndef LIGHT_H
#define LIGHT_H
//Purpose: This file contains the class definition for the Light class

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
#include <vector>
#include <cmath>
#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <atomic>


#include "points.h"
#include "colorf.h"

auto light_enable() -> void;
auto light_disable() -> void;

static std::atomic<unsigned int> light_id(0);

class Light{
    public:
        unsigned int _id;
        char type;
        Point position;
        Point direction;
        float cutoff;

        Light(Point position, Point direction, float cutoff);
        Light(Point position);
        Light(int o,Point direction);
        
        auto show() -> void ;
        auto render() -> void ;
        auto on() -> void;
        auto off() -> void;
};

class Reflection{
    public:
        bool has_material;
        Color ambient;
        Color diffuse;
        Color specular;
        Color emissive;
        float shininess;

        Reflection(Color ambient, Color diffuse, Color specular, Color emissive, float shininess);
        Reflection();

        auto show() -> void;
        auto apply() -> void;
};

#endif