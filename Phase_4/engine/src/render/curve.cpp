#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include "curve.h"
#include "points.h"

using namespace std;


float catmullrom_matrix[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
					 { 1.0f, -2.5f,  2.0f, -0.5f},
					 {-0.5f,  0.0f,  0.5f,  0.0f},
					 { 0.0f,  1.0f,  0.0f,  0.0f} };

Curve::Curve(vector<Point> points){
    this->control_points = points;
    this->POINT_COUNT = points.size();
    this->position = Point(0,0,0);
    this->derivated = Point(0,0,0);
    this->previous_y = Point(0,-1,0);
}

Curve::Curve(){
    this->control_points = vector<Point>();
    this->POINT_COUNT = 0;
    this->position = Point(0,0,0);
    this->derivated = Point(0,0,0);
    this->previous_y = Point(0,-1,0);
}

auto Curve::add_control_point(Point p) -> void{
    this->control_points.push_back(p);
    this->POINT_COUNT++;
}

auto Curve::get_control_point(int index) -> Point{
    return this->control_points[index];
}

auto Curve::get_control_points() -> vector<Point>{
    return this->control_points;
}

auto Curve::get_control_points_count() -> int{
    return this->POINT_COUNT;
}

auto Curve::get_position() -> Point{
    return this->position;
}

auto Curve::get_derivated() -> Point{
    return this->derivated;
}

auto Curve::get_previous_y() -> Point{
    return this->previous_y;
}

auto Curve::set_previous_y(Point p) -> void{
    this->previous_y = p;
}

auto Curve::get_catmullrom_point(float t, Point p0, Point p1, Point p2, Point p3) -> void{
	float fpoint0[3] = {p0.x,p0.y,p0.z};
	float fpoint1[3] = {p1.x,p1.y,p1.z};
	float fpoint2[3] = {p2.x,p2.y,p2.z};
	float fpoint3[3] = {p3.x,p3.y,p3.z};

	float pos[3];
	float deriv[3];
	for (int i = 0; i<3 ; i++){
		float p[4] = {fpoint0[i],fpoint1[i],fpoint2[i],fpoint3[i]};
		float a[4];
		mult_matrix_vector(catmullrom_matrix, p, a);
		pos[i] = a[0]*pow(t,3) + a[1]*pow(t,2) + a[2]*t + a[3];
		deriv[i] = 3*a[0]*pow(t,2) + 2*a[1]*t + a[2];
	}
	this->position = Point(pos[0],pos[1],pos[2]);
	this->derivated = Point(deriv[0],deriv[1],deriv[2]);
}



auto Curve::get_global_catmullrom(float gt) -> void{
	if (this->POINT_COUNT < 4);
		//throw exception
	
	float t = gt * this->POINT_COUNT;
	int index = floor(t);  
	t = t - index; 

	// indices store the points
	int indices[4];
	indices[0] = (index + this->POINT_COUNT - 1) % this->POINT_COUNT;
	indices[1] = (indices[0] + 1) % this->POINT_COUNT;
	indices[2] = (indices[1] + 1) % this->POINT_COUNT;
	indices[3] = (indices[2] + 1) % this->POINT_COUNT;

	this->get_catmullrom_point(t, this->control_points[indices[0]], this->control_points[indices[1]], this->control_points[indices[2]], this->control_points[indices[3]]);
}

auto Curve::get_tangent(float) -> Point{
    return Point();
}

auto Curve::get_normal(float) -> Point{
    return Point();

}

void build_rotmatrix(float *x, float *y, float *z, float *m) {
	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *a) {
	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

float length(float *v) {
	float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return res;
}

void mult_matrix_vector(float m[4][4], float *v, float *res) {
	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j][k];
		}
	}
}
