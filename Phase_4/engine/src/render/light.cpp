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
#include <regex>
#include <string>
#include <fstream>
#include <sstream>


#include "points.h"
#include "light.h"
#include "colorf.h"

using namespace std;

auto light_enable() -> void{
    cout << "Lighting enabled" << endl;
    glEnable(GL_LIGHTING);
    float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}

auto light_disable() -> void{
    glDisable(GL_LIGHTING);
}

Light::Light(Point position, Point direction, float cutoff){
    this->_id = light_id++;
    this->type = 's';
    this->position = position;
    this->direction = direction;
    this->cutoff = cutoff;
}

Light::Light(Point position){
    this->_id = light_id++;
    this->type = 'p';
    this->position = position;
}

Light::Light(int _o,Point direction){
    this->_id = light_id++;
    this->type = 'd';
    this->direction = direction;
}

auto Light::show() -> void{
    if(this->type == 's'){
        cout << "Position: " << this->position.x << ", " << this->position.y << ", " << this->position.z << endl;
        cout << "Direction: " << this->direction.x << ", " << this->direction.y << ", " << this->direction.z << endl;
        cout << "Cutoff: " << this->cutoff << endl;
    }
    else if(this->type == 'p'){
        cout << "Position: " << this->position.x << ", " << this->position.y << ", " << this->position.z << endl;
    }
    else if(this->type == 'd'){
        cout << "Direction: " << this->direction.x << ", " << this->direction.y << ", " << this->direction.z << endl;
    }
}

auto Light::render() -> void{
    if(this->type == 's'){
        GLfloat light_position[] = {this->position.x, this->position.y, this->position.z, 1.0};
        GLfloat light_direction[] = {this->direction.x, this->direction.y, this->direction.z};
        glLightfv(GL_LIGHT0 + this->_id, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0 + this->_id, GL_SPOT_DIRECTION, light_direction);
        glLightf(GL_LIGHT0 + this->_id, GL_SPOT_CUTOFF, this->cutoff);
    }
    else if(this->type == 'p'){
        GLfloat light_position[] = {this->position.x, this->position.y, this->position.z, 1.0};
        glLightfv(GL_LIGHT0 + this->_id, GL_POSITION, light_position);
    }
    else if(this->type == 'd'){
        GLfloat light_direction[] = {this->direction.x, this->direction.y, this->direction.z};
        glLightfv(GL_LIGHT0 + this->_id, GL_POSITION, light_direction);
    }
}

auto Light::on() -> void{
    cout << "Light " << this->_id << " on" << endl;
    glEnable(GL_LIGHT0 + this->_id);
    float dark[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4] = {1.0, 1.0, 1.0, 1.0};
    float black[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    // light colors
    glLightfv(GL_LIGHT0 + this->_id, GL_AMBIENT, dark);
    glLightfv(GL_LIGHT0 + this->_id, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0 + this->_id, GL_SPECULAR, white);
}

auto Light::off() -> void{
    glDisable(GL_LIGHT0 + this->_id);
}


Reflection::Reflection(Color ambient, Color diffuse, Color specular, Color emissive, float shininess){
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->emissive = emissive;
    this->shininess = shininess;
}

Reflection::Reflection(){
    this->ambient = Color((float)200/255, (float)200/255, (float)200/255);
    this->diffuse = Color((float)50/255, (float)50/255, (float)50/255);
    this->specular = Color((float)0, (float)0, (float)0);
    this->emissive = Color((float)0, (float)0, (float)0);
    this->shininess = 0;
}

auto Reflection::apply() -> void{

    float ambient[4] = {this->ambient.r, this->ambient.g, this->ambient.b, 1.0};
    float diffuse[4] = {this->diffuse.r, this->diffuse.g, this->diffuse.b, 1.0};
    float specular[4] = {this->specular.r, this->specular.g, this->specular.b, 1.0};
    float emissive[4] = {this->emissive.r, this->emissive.g, this->emissive.b, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emissive);
    glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);
}

auto Reflection::show() -> void{
    cout << "Materials" << endl;
    cout << "Ambient: " << this->ambient.sshow() << endl;
    cout << "Diffuse: " << this->diffuse.sshow() << endl;
    cout << "Specular: " << this->specular.sshow() << endl;
    cout << "Emissive: " << this->emissive.sshow() << endl;
    cout << "Shininess: " << this->shininess << endl;
}
