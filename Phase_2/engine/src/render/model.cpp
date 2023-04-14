#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <regex>
#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>

#include "points.h"
#include "model.h"

using namespace std;

const regex text_regex("[\\w ]+(?=\\.3d)");
smatch base_match;

Model::Model(string file, vector<Point> points, string texture, Color color) {
    this->file = file;
    this->points = points;
    this->texture = texture;
    this->color = color;
}

Model::Model(string file){
    this->file = file;
    this->points = vector<Point>();
    this->texture = "";
    this->color = Color("#FFFFFF");
}

Model::Model(string file, Color color){
    this->file = file;
    this->points = vector<Point>();
    this->texture = "";
    this->color = color;
}

Model::Model(){
    this->file = "";
    this->points = vector<Point>();
    this->texture = "";
    this->color = Color("#FFFFFF");
}


auto Model::show() -> void {
	cout << "File: " << this->file << endl;
	cout << "Points: " << this->points.size() << endl;
	cout << "Texture: " << this->texture << endl;
	cout << "Color: " << this->color.r << " " << this->color.g << " " << this->color.b << endl;
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
	this->color.apply();
	for (Point point : this->points){
		glVertex3f(point.getX(), point.getY(), point.getZ());
	}
	glEnd();
	//cout << "Model rendered" << endl;
}
