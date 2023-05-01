//Purpose: Header file for parser.cpp
#ifndef PARSER_H
#define PARSER_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <string>

#include "points.h"
#include "model.h"
#include "scene.h"
#include "group.h"
#include "transformation.h"
#include "camera.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class Parser {

    public:
        std::string file;

        Parser(std::string file);
        auto parse() -> Scene;

        auto parse_group(XMLElement* element_group) -> Group;
        auto parse_models(XMLElement* models_element) -> std::vector<Model>;
        auto parse_transformations(XMLElement* transformation_element) -> std::vector<Transformation>;
        auto parse_camera(XMLElement* camera_element, int screen_width, int screen_height ) -> Camera;

};

#endif