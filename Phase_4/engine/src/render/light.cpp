#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <regex>
#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>


#include "points.h"
#include "light.h"
#include "colorf.h"

using namespace std;

/*

Light_Point::Light_Point(Point position, Color color){
    this->position = position;
    this->color = color;
}

auto Light_Point::show() -> void{
    cout << "Light_Point" << endl;
    cout << "Position: ";
    this->position.show();
    cout << "Color: ";
    this->color.show();
}

auto Light_Point::render() -> void{
    float pos[4] = {this->position.x, this->position.y, this->position.z, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}


*/
