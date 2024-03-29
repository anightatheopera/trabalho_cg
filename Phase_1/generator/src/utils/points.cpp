#include <cmath>
#include <sstream>


#include "points.h"


Point::Point(double _x, double _y, double _z){
	x = _x;
	y = _y;
	z = _z;
}

double Point::getX() {
	return x;
}

double Point::getY() {
	return y;
}

double Point::getZ() {
	return z;
}

void Point::setX(double x){
	this->x = x;
}

void Point::setY(double y){
	this->y = y;
}

void Point::setZ(double z){
	this->z = z;
}

void Point::substract(Point p){
	x -= p.getX();
	y -= p.getY();
	z -= p.getZ();
}

