#include <cstdlib>
#include <vector>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>

#include "points.h"
#include "bezier.h"

using namespace std;

BezierPatch::BezierPatch(int tessellation, int n_patches, int n_points, vector<vector<int>> indices, vector<Point> control_points) {
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


vector<string> split (const string &s, char delim) {
	vector<string> result;
    	stringstream ss(s);
    	string item;

    	while (getline (ss, item, delim)) {
        	result.push_back (item);
	    }

    	return result;
}


vector<Point> draw_patch(int tesselation, std::string patch_file){ // Draw a patch from a file
	BezierPatch patch = load_patch(tesselation, patch_file);
	vector<Point> points;
	
	return points;
}

BezierPatch load_patch(int tessalation, string file){ // Load a patch from a file
	ifstream patch_file;
	patch_file.open(file);
	string line;
	int n_patches, n_control_points;
	vector<vector<int>> patch_index;
	vector<Point> control_points;

	if(patch_file.is_open()){
		getline(patch_file, line); //Get number of patches
		n_patches = atoi(line.c_str());
		for(int patch = 0; patch < n_patches; patch++){ // For each patch get the indexes of the control points
			getline(patch_file , line);
			patch_index.push_back(vector<int>());
			vector<string> split_line = split(line, ','); // Split the line by the commas
			for (int index = 0; index < 16; index++){
				patch_index[patch].push_back(atoi(split_line[index].c_str()));
			}
		}
		getline(patch_file, line); // Get number of control points
		n_control_points = atoi(line.c_str());
		for (int control_point = 0; control_point < n_control_points; control_point++){ // For each control point get the coordinates
			getline(patch_file, line);
			float x, y, z;
			vector<string> split_line = split(line, ','); // Split the line by the commas
			x = atof(split_line[0].c_str());
			y = atof(split_line[1].c_str());
			z = atof(split_line[2].c_str());
			control_points.push_back(Point(x, y, z));
		}
	}
	return BezierPatch(tessalation, n_patches, n_control_points, patch_index, control_points);
}
