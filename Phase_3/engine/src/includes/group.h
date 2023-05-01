//Purpose: Header file for Group class
#ifndef GROUP_H
#define GROUP_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <memory>

#include "model.h"
#include "transformation.h"

using namespace std;

class Group {
        
        public:
                string name;
                vector<Group> subgroups;
                vector<Model> models;
                vector<Transformation> transformations;

                Group(vector<Group> subgroups, vector<Model> models, vector<Transformation> transformations, string name);
                Group();

                auto show() -> void;
                auto pprint(int ident) -> void;
                auto pprint() -> void;
                auto set_name(string name) -> void;
                auto addSubgroup(Group subgroup) -> void;
                auto addModel(Model model) -> void;
                auto addTransformation(Transformation transformation) -> void;
                auto applyTransformations();
                auto render(bool picker = false) -> void;
                auto load_models() -> void;
                auto vbo__init__() -> void;
};

#endif
