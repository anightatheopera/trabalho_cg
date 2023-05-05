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

	this->name = "";
    	this->subgroups = vector<Group>();
    	this->models = vector<Model>();
    	this->transformations = vector<Transformation>();
}

Group::Group(vector<Group> subgroups, vector<Model> models, vector<Transformation> transformations, string name){
    this->name = name;
    this->subgroups = subgroups;
    this->models = models;
    this->transformations = transformations;
}

auto Group::pprint() -> void {
    cout << "-----------------------" << endl;
    this->pprint(0);
    cout << "-----------------------" << endl;
}

auto Group::pprint(int ident) -> void {
    // print in groups recursively in a tree format
    for (int i = 0; i < ident; i++){
        cout << " ";
    }
    cout << "Group - " << this->name << endl;
    for (Group subgroup : this->subgroups){
        subgroup.pprint(ident + 1);
    }
    for (auto transformation : this->transformations){
	for (int i = 0; i < ident + 1; i++){
	    cout << " ";
	}
	cout << transformation.show();
    }
    for (Model model : this->models){
        for (int i = 0; i < ident + 1; i++){
            cout << " ";
        }
        cout << "Model: " << model.file << "; " << model.points.size() << endl;
    }

}

auto Group::show() -> void {
    cout << "Subgroups: " << this->subgroups.size() << endl;
    cout << "Models: " << this->models.size() << endl;
    cout << "Transformations: " << this->transformations.size() << endl;
}

auto Group::set_name(string name) -> void {
    this->name = name;
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

auto Group::applyTransformations(bool lines){
    for (Transformation oper : this->transformations){
        oper.apply(lines);
    }
}

auto Group::render(bool picker,bool lines) -> void {
    glPushMatrix();
    this->applyTransformations(lines);
    //this->pprint();
    for (Model model : this->models){
	model.render();
    }
    for (Group subgroup : this->subgroups){
        subgroup.render();
    }
    glPopMatrix();

}

auto Group::vbo__init__() -> void {
    for (Model &model : this->models){
        model.prepare_data();
    }

    for (Group &subgroup : this->subgroups){
        subgroup.vbo__init__();
    }
}

auto Group::load_models() -> void {
    for (Model &model : this->models){
        model.load_file();
    }

    for (Group &subgroup : this->subgroups){
        subgroup.load_models();
    }
}



