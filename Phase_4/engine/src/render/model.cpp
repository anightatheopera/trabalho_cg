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
#include <regex>
#include <string>
#include <fstream>
#include <sstream>

#include "points.h"
#include "model.h"
#include "colorf.h"
#include "light.h"

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

Model::Model(string file, string texture, Color color){
	this->file = file;
	this->points = vector<Point>();
	this->texture = texture;
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

Point calculate_normal(Point *p){
	float vec_u[3] = {p[1].x - p[0].x, p[1].y - p[0].y, p[1].z - p[0].z};
	float vec_v[3] = {p[2].x - p[0].x, p[2].y - p[0].y, p[2].z - p[0].z};

	float x = vec_u[2] * vec_v[2] - vec_u[2] * vec_v[1];
	float y = vec_u[2] * vec_v[0] - vec_u[0] * vec_v[2];
	float z = vec_u[0] * vec_v[1] - vec_u[1] * vec_v[0];

	return Point(x, y, z);
}

auto Model::load_file() -> void{
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
}

auto Model::load_normals() -> void{
	for (int i = 0; i < this->points.size(); i++){
		Point p[3] = {this->points[i], this->points[i+1], this->points[i+2]};
		Point normal = calculate_normal(p);
		normal.normalize();
		this->normals_vectors.push_back(normal);
	}
	this->normal_count = this->normals_vectors.size()/3;
}

auto Model::load_texture() -> void{
	if (this->texture == ""){
		return;
	}
	ilInit();
	ILuint image;
	ilGenImages(1, &image);
	ilBindImage(image);
	ilLoadImage((ILstring)this->texture.c_str());
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	this->texture_width = ilGetInteger(IL_IMAGE_WIDTH);
	this->texture_height = ilGetInteger(IL_IMAGE_HEIGHT);
	this->texture_data = ilGetData();

}

auto Model::prepare_data() -> void {
	// points, normals, textures
	vector<float> p,n,t;

	for (Point point : this->points){
		p.push_back(point.x);
		p.push_back(point.y);
		p.push_back(point.z);
	}
	for (Point point : this->normals_vectors){
		n.push_back(point.x);
		n.push_back(point.y);
		n.push_back(point.z);
	}

    for (int i = 1; i < this->texture_width - 2; i++) {
        for (int j = 1; j < this->texture_height - 1; j++) {
			// no clue why this works, but it does, i just follow the instructions
			t.push_back(i+1);
			t.push_back(j);
			t.push_back(i);
			t.push_back(j);
        }
    }
	this->vertice_count = p.size() / 3;

// vertices vao
	glGenVertexArrays(1, &(this->vertices_vao));
	glBindVertexArray(this->vertices_vao);

// vertices vbo
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

// criar VBO para a textura
glGenBuffers(1, &(this->texcoords));
glBindBuffer(GL_ARRAY_BUFFER, this->texcoords);
glBufferData(
	GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
	sizeof(float) * t.size(), // tamanho do vector em bytes
	t.data(), // os dados do array associado ao vector
	GL_STATIC_DRAW // indicativo da utilização (estático e para desenho)
);
glVertexAttribPointer(
	1, // índice do atributo
	2, // número de componentes (x, y)
	GL_FLOAT, // tipo dos componentes
	GL_FALSE, // normalização
	0, // stride
	0 // offset
);

glEnableVertexAttribArray(0); //posição do vertice
glEnableVertexAttribArray(1); //posição da textura

// desligar o VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

auto Model::init() -> void {
	//cout << "Initializing model" << endl;
	this->load_file();
	this->load_normals();
	this->load_texture();
	this->prepare_data();
	//cout << "Model initialized" << endl;
}
auto Model::render() -> void {
	this->color.apply();
	glBindVertexArray(this->vertices_vao);
	glBindTexture(GL_TEXTURE_2D, this->texcoords);
	glDrawArrays(GL_TRIANGLES, 0, this->vertice_count);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
}
