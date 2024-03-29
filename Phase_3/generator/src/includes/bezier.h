//Purpose: Header file for bezier.cpp
#ifndef BEZIER_H
#define BEZIER_H
#include <vector>
#include "points.h"

using namespace std;

class BezierPatch {
	public:
		int tessellation;
		int n_patches;
		int n_points;
		vector<vector<int>> indices;
		vector<Point> control_points;

		BezierPatch(int tessellation, int n_patches, int n_points, vector<vector<int>> indices, vector<Point> control_points);
		BezierPatch();

};

#endif

