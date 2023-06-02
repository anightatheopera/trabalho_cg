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


#include "points.h"
#include "colorf.h"


/*
class Light{
    public:
        virtual auto show() -> void;
        virtual auto render() -> void;
        auto enable() -> void;
};

class Light_Point : public Light{
    public:
        Point position;

        Light_Point(Point position,);
        
        auto show() -> void;
        auto render() -> void;
        auto set() -> void;
};

class Light_Directional : public Light{
    public:
        Point direction;

        Light_Directional(Point direction);
        
        auto show() -> void;
        auto render() -> void;
        auto set() -> void;
};

class Light_Spot : public Light{
    public:
        Point position;
        Point direction;
        float cutoff;

        Light_Spot(Point position, Point direction, float cutoff);
        
        auto show() -> void;
        auto render() -> void;
        auto set() -> void;
};
*/
class Reflection{
    public:
        Color ambient;
        Color diffuse;
        Color specular;
        Color emissive;
        float shininess;

        Reflection(Color ambient, Color diffuse, Color specular, Color emissive, float shininess);
        Reflection();
        
        auto show() -> void;
        auto render() -> void;
        auto set() -> void;
};






#endif