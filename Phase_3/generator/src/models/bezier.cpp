#include <cstdlib>
#include <vector>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>

#define _USE_MATH_DEFINES
#include <math.h>

#include "points.h"
#include "models.h"
#include "bezier.h"

BezierPatch::BezierPatch(int tessellation, int n_patches, int n_points, std::vector<std::vector<int>> indices, std::vector<Point> control_points) {
	this->tessellation = tessellation;
	this->n_patches = n_patches;
	this->n_points = n_points;
	this->indices = indices;
	this->control_points = control_points;
}

BezierPatch::BezierPatch() {
	this->tessellation = 0;
	this->n_patches = 0;
	this->n_points = 0;
	this->indices = {};
	this->control_points = {};
}


std::vector<string> split (const string &s, char delim) {
	std::vector<string> result;
    	stringstream ss(s);
    	string item;

    	while (getline (ss, item, delim)) {
        	result.push_back (item);
	    }

    	return result;
}

Point bernstein(float t, Point p1, Point p2, Point p3, Point p4){
	float x, y, z;
	auto poly1 = pow((1 - t), 3);
	auto poly2 = 3 * t * pow((1 - t), 2);
	auto poly3 = 3 * pow(t, 2) * (1 - t);
	auto poly4 = pow(t, 3);

	x = poly1 * p1.x + poly2 * p2.x + poly3 * p3.x + poly4 * p4.x;
	y = poly1 * p1.y + poly2 * p2.y + poly3 * p3.y + poly4 * p4.y;
	z = poly1 * p1.z + poly2 * p2.z + poly3 * p3.z + poly4 * p4.z;
	return Point(x, y, z);
}

Point bezier(float t, float tt, std::vector<Point> points, std::vector<int> indexes){
	Point initial[4] = {Point(), Point(), Point(), Point()};
	std::vector<Point> curve;
	int i, j = 0;
	for (i = 0; i < 16; i++){
		initial[j] = Point(points[indexes[i]].x, points[indexes[i]].y, points[indexes[i]].z);
		if(j == 3) {
			curve.push_back(bernstein(t, initial[0], initial[1], initial[2], initial[3]));
			j = 0;
		}
		else j++;
	}
	return bernstein(tt, curve[0], curve[1], curve[2], curve[3]);
}

BezierPatch load_patch(int tessalation, string file){ // Load a patch from a file
	ifstream patch_file;
	patch_file.open(file);
	string line;
	int n_patches, n_control_points;
	std::vector<std::vector<int>> patch_index;
	std::vector<Point> control_points;

	if(patch_file.is_open()){
		getline(patch_file, line); //Get number of patches
		n_patches = atoi(line.c_str());
		for(int patch = 0; patch < n_patches; patch++){ // For each patch get the indexes of the control points
			getline(patch_file , line);
			patch_index.push_back(std::vector<int>());
			std::vector<string> split_line = split(line, ','); // Split the line by the commas
			for (int index = 0; index < 16; index++){
				patch_index[patch].push_back(atoi(split_line[index].c_str()));
			}
		}
		getline(patch_file, line); // Get number of control points
		n_control_points = atoi(line.c_str());
		for (int control_point = 0; control_point < n_control_points; control_point++){ // For each control point get the coordinates
			getline(patch_file, line);
			float x, y, z;
			std::vector<string> split_line = split(line, ','); // Split the line by the commas
			x = atof(split_line[0].c_str());
			y = atof(split_line[1].c_str());
			z = atof(split_line[2].c_str());
			control_points.push_back(Point(x, y, z));
		}
	}
	return BezierPatch(tessalation, n_patches, n_control_points, patch_index, control_points);
}

std::vector<Point> draw_patch(int tesselation, std::string patch_file){ // Draw a patch from a file
	BezierPatch patch = load_patch(tesselation, patch_file);
	std::vector<Point> points;
	for (int i = 0; i < patch.n_patches; i++){
		float increment = 1.0 / tesselation; // Incremento
		for (float x_axis = 0; x_axis < 1; x_axis += increment){
			for (float y_axis = 0; y_axis < 1; y_axis += increment){
				Point out_point[4] = {bezier(x_axis, y_axis, patch.control_points, patch.indices[i]),
								bezier(x_axis, y_axis + increment, patch.control_points, patch.indices[i]),
								bezier(x_axis + increment, y_axis, patch.control_points, patch.indices[i]),
								bezier(x_axis + increment, y_axis + increment, patch.control_points, patch.indices[i])
								};

				points.push_back(out_point[0]);
				points.push_back(out_point[2]);
				points.push_back(out_point[3]);
				points.push_back(out_point[0]);
				points.push_back(out_point[3]);
				points.push_back(out_point[1]);
			}
		}
	}
	return points;
}
