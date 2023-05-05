#ifndef MODEL_H
#define MODEL_H
//Purpose: This file contains the class definition for the Model class

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
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


#include "points.h"
#include "colorf.h"

class Model {

    public:
	    std::string file;
	    std::vector<Point> points;
	    std::string texture;
            GLuint vertices = 0;
            GLuint vao = 0;
            GLint vertice_count = 0;
	    Color color;

        //Texture;
        //Material;
        //Transformations;
        //Animation;
        //Light;

        Model(std::string file, std::vector<Point> points,std::string texture, Color color);
        Model(std::string file);
	Model(std::string file, Color color);
	Model();

        auto show() -> void;

        auto load_file() -> void;
        auto prepare_data() -> void;
        auto render() -> void;

};

#endif
