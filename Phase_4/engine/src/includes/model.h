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

#include <IL/il.h>

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
#include "light.h"

class Model {
        public:
                std::string file;
                std::string texture;
                std::vector<Point> points;
                std::vector<Point> normal_vectors;
                std::vector<Point> texture_points;
                Color color;
                //Reflection reflection;
                GLint vertice_count = 0;
                GLint normal_count = 0;
                GLint texture_count = 0;

                int texture_width = 0;
                int texture_height = 0;
                ILubyte * texture_data = nullptr;

                GLuint vertices = 0;
                GLuint vertices_vao = 0;
                GLuint normal = 0;
                GLuint normal_vao = 0;
                GLuint textures = 0;
                GLuint textures_vao = 0;
                GLuint texture_id = 0;
                uint32_t image_id = 0;

                Model(std::string file, std::vector<Point> points,std::string texture, Color color);
                Model(std::string file);
                Model(std::string file, Color color);
                Model(std::string file, std::string texture, Color color);
                //Model(std::string file, std::string texture, Color color, Reflection reflection);
                Model();

                auto show() -> void;
                auto init() -> void;

                auto load_file() -> void;
                auto load_texture() -> void;
                auto prepare_data() -> void;
                auto render() -> void;

};

#endif
