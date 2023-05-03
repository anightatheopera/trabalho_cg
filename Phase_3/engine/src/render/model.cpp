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
		cout << "Error opening file `" << this->file << "`" << endl;
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

auto Model::prepare_data() -> void {
// criar um vector com os dados dos pontos
	vector<float> p;
	for (Point point : this->points){
		p.push_back(point.x);
		p.push_back(point.y);
		p.push_back(point.z);
	}
	this->vertice_count = p.size() / 3;

// criar o VAO
	glGenVertexArrays(1, &(this->vao));
	glBindVertexArray(this->vao);

// criar o VBO
	glGenBuffers(1, &(this->vertices));

// copiar o vector para a memória gráfica
	glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
	glBufferData(
		GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
		sizeof(float) * p.size(), // tamanho do vector em bytes
		0, // os dados do array associado ao vector
		GL_STATIC_DRAW // indicativo da utilização (estático e para desenho)
	); 
	glBufferSubData(
		GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
		0, // offset
		sizeof(float) * p.size(), // tamanho do vector em bytes
		p.data() // os dados do array associado ao vector
	);

// indicar que o VBO está associado ao VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0, // índice do atributo
		3, // número de componentes (x, y, z)
		GL_FLOAT, // tipo dos componentes
		GL_FALSE, // normalização
		0, // stride
		0 // offset
	);

// desligar o VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

auto Model::render() -> void {
	//cout << "Rendering model" << endl;
	//this->show();
	//
	
	this->color.apply();
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, this->vertice_count);

	glBindVertexArray(0);
	
	/*
	-- Old render method --
	glBegin(GL_TRIANGLES);
	this->color.apply();
	for (Point point : this->points){
		glVertex3f(point.getX(), point.getY(), point.getZ());
	}
	glEnd();

	cout << "Model rendered" << endl;
	*/

}
