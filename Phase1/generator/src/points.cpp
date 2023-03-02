#include <cmath>
#include <sstream>

#include "points.h"

Point::Point(double _x, double _y, double _z){
	x = _x;
	y = _y;
	z = _z;
}

Point::Point(const Point& p){
	x = p.x;
	y = p.y;
	z = p.z;
}

double Point::getX() const{
	return x;
}

double Point::getY() const{
	return y;
}

double Point::getZ() const{
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

