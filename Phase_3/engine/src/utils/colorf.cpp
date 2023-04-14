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
#include <string>
#include <fstream>
#include <sstream>

#include "colorf.h"

using namespace std;

Color::Color(float r, float g, float b) {
  this->r = r;
  this->g = g;
  this->b = b;
}

Color::Color(string hex) {
	
	int r, g, b;
    	sscanf(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
	
	this->r = r/255.0;
    	this->g = g/255.0;
    	this->b = b/255.0;
}

Color::Color() {
  this->r = 1.0f;
  this->g = 1.0f;
  this->b = 1.0f;
}


auto Color::apply() -> void {
  glColor3f(this->r, this->g, this->b);
}


auto Color::show() -> void {
  cout << "R: " << this->r << " G: " << this->g << " B: " << this->b << endl;
}
