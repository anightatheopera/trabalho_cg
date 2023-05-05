//Purpose: Header file for Curve class
#ifndef CURVE_H
#define CURVE_H

#include <vector>

#include "points.h"
using namespace std;

class Curve{
	private:
		vector<Point> control_points;
		int POINT_COUNT;
		Point position;
		Point derivated;
		Point previous_y;
    
    	public:
        	Curve(vector<Point> points);
        	Curve();

		auto add_control_point(Point p) -> void;
		auto get_control_point(int index) -> Point;
		auto get_control_points() -> vector<Point>;
		auto get_control_points_count() -> int;


		auto get_position() -> Point;
		auto get_derivated() -> Point;

		auto get_previous_y() -> Point;
		auto set_previous_y(Point p) -> void;

		auto get_catmullrom_point(float, Point, Point, Point, Point) -> void;
		auto get_global_catmullrom(float) -> void;
        	auto get_tangent(float) -> Point;
        	auto get_normal(float) -> Point;


};

void mult_matrix_vector(float[4][4], float*, float*);
void build_rotmatrix(float *, float *, float*, float*);
void cross(float *, float *, float*);
void normalize(float*);
float length(float*);

#endif
