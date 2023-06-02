#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cmath>
#include <sstream>

#include "points.h"

Point::Point(float _x, float _y, float _z){
	x = _x;
	y = _y;
	z = _z;
}

Point::Point(){
	x = 0;
	y = 0;
	z = 0;
}

float Point::getX() {
	return x;
}

float Point::getY() {
	return y;
}

float Point::getZ() {
	return z;
}

void Point::setX(float x){
	this->x = x;
}

void Point::setY(float y){
	this->y = y;
}

void Point::setZ(float z){
	this->z = z;
}

void Point::normalize(){
	float norm = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	x /= norm;
	y /= norm;
	z /= norm;
}

