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

#include "points.h"
#include "group.h"
#include "model.h"
#include "transformation.h"

using namespace std;

Group::Group(){
    this->subgroups = vector<Group>();
    this->models = vector<Model>();
    this->transformations = vector<Transformation>();
}

Group::Group(vector<Group> subgroups, vector<Model> models, vector<Transformation> transformations){
    this->subgroups = subgroups;
    this->models = models;
    this->transformations = transformations;
}

auto Group::show() -> void {
    cout << "Subgroups: " << this->subgroups.size() << endl;
    cout << "Models: " << this->models.size() << endl;
    cout << "Transformations: " << this->transformations.size() << endl;
}

auto Group::addSubgroup(Group subgroup) -> void {
    this->subgroups.push_back(subgroup);
}

auto Group::addModel(Model model) -> void {
    this->models.push_back(model);
}

auto Group::addTransformation(Transformation transformation) -> void {
    this->transformations.push_back(transformation);
}

auto Group::applyTransformations(){
    for (Transformation oper : this->transformations){
        oper.apply();
    }
}

auto Group::render() -> void {
    glPushMatrix();
    this->applyTransformations();
    //glColor3f((float)219/255, (float)112/255, (float)147/255);
    for (Model model : this->models){
        model.render();
    }
    for (Group subgroup : this->subgroups){
        subgroup.render();
    }
    glPopMatrix();
}

auto Group::load_models() -> void {
    for (Model model : this->models){
        model.load_file();
    }
    for (Group subgroup : this->subgroups){
        subgroup.load_models();
    }
}



