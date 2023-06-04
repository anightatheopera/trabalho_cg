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

void Point::substract(Point p){
	x -= p.getX();
	y -= p.getY();
	z -= p.getZ();
}

void Point::normalize(){
	float norm = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	x /= norm;
	y /= norm;
	z /= norm;
}

Point3::Point3(Point p, Point n, float t[2]){
	this->p = p;
	this->n = n;
	this->t[0] = t[0];
	this->t[1] = t[1];
}

Point3::Point3(Point p, Point n){
	this->p = p;
	this->n = n;
	this->t[0] = 0;
	this->t[1] = 0;
}

Point3::Point3(){
	this->p = Point();
	this->n = Point();
	this->t[0] = 0;
	this->t[1] = 0;
}

Point3::Point3(Point p, Point n, Point t){
	this->p = p;
	this->n = n;
	this->t[0] = t.getX();
	this->t[1] = t.getY();
}

auto cross(Point a, Point b) -> Point {
	Point res;
	res.x = a.y*b.z - a.z*b.y;
	res.y = a.z*b.x - a.x*b.z;
	res.z = a.x*b.y - a.y*b.x;
	return res;
}

auto normal(Point a, Point b, Point c) -> Point {
	Point ab = Point(b.x - a.x, b.y - a.y, b.z - a.z);
	Point ac = Point(c.x - a.x, c.y - a.y, c.z - a.z);
	Point res = cross(ab, ac);
	res.normalize();
	return res;
}
