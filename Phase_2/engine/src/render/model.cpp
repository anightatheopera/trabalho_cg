#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

#include "points.h"
#include "model.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

Model::Model(string file, vector<Point> points){
    this->file = file;
    this->points = points;
}

Model::Model(string file){
    this->file = file;
	this->points = vector<Point>();
}

auto Model::show() -> void {
	cout << "File: " << this->file << endl;
	cout << "Points: " << this->points.size() << endl;
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

auto Model::load_file() -> void{
	//cout << "Loading file" << endl;
	ifstream file;
	file.open(this->file);
	if (!file.is_open()){
	//	cout << "Error opening file `" << this->file << "`" << endl;
		exit(1);
	}
	string line;
	getline(file, line);
	while(getline(file, line)){
		vector<string> tokens = split(line, ';');
		for (auto point : tokens){
			vector<string> coords = split(point, ',');
			Point p;
			p.setX(stod(coords[0]));
			p.setY(stod(coords[1]));
			p.setZ(stod(coords[2]));
			this->points.push_back(p);
		}
	}
	file.close();
	//cout << "File loaded" << endl;	
}

auto Model::render() -> void {
	//cout << "Rendering model" << endl;
	//this->show();
	glBegin(GL_TRIANGLES);
	for (Point point : this->points){
		glVertex3f(point.getX(), point.getY(), point.getZ());
	}
	glEnd();
	//cout << "Model rendered" << endl;
}
