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
			vector<string> point3 = split(point, ':');
			vector<string> coords = split(point3[0], ',');
			vector<string> normals = split(point3[1], ',');
			vector<string> textures = split(point3[2], ',');
			Point pos;
			pos.setX(stod(coords[0]));
			pos.setY(stod(coords[1]));
			pos.setZ(stod(coords[2]));
			this->points.push_back(pos);
			Point normal;
			normal.setX(stod(normals[0]));
			normal.setY(stod(normals[1]));
			normal.setZ(stod(normals[2]));
			this->normal_vectors.push_back(normal);
			Point texture;
			texture.setX(stod(textures[0]));
			texture.setY(stod(textures[1]));
			texture.setZ(0);
			this->texture_points.push_back(texture);
		}
	}
	file.close();
}

int loadTexture(std::string s) {
    unsigned int t, tw, th;
    unsigned char* texData;
    unsigned int texID;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring) s.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        tw,
        th,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;
}

auto Model::load_texture() -> void{
	if (this->texture == ""){
		return;
	}
	std::cout << "Loading texture: " << this->texture << std::endl;
	this->texture_id = loadTexture(this->texture);
	// isto deve funcionar bem para carregar a imagem.
}

auto Model::prepare_data() -> void {
	// points, normals, textures
	vector<float> p,n,t;

	for (int vertex = 0; vertex< this->points.size(); vertex++){
		p.push_back(this->points[vertex].x);
		p.push_back(this->points[vertex].y);
		p.push_back(this->points[vertex].z);

		n.push_back(this->normal_vectors[vertex].x);
		n.push_back(this->normal_vectors[vertex].y);
		n.push_back(this->normal_vectors[vertex].z);

		t.push_back(this->texture_points[vertex].x);
		t.push_back(this->texture_points[vertex].y);
	}

	this->vertice_count = p.size() / 3;
	this->normal_count = n.size() / 3;
	this->texture_count = t.size() / 2;

// VERTICES
	//VAO
	glGenVertexArrays(1, &(this->vertices_vao));
	glBindVertexArray(this->vertices_vao);

	//VBO
	glGenBuffers(1, &(this->vertices));

	//Copy
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
	//Associate
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0, // índice do atributo
		3, // número de componentes (x, y, z)
		GL_FLOAT, // tipo dos componentes
		GL_FALSE, // normalização
		0, // stride
		0 // offset
	);

	//UNBIND
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

// NORMALS

	//VBO
	glGenBuffers(1, &(this->normal));
	glBindBuffer(GL_ARRAY_BUFFER, this->normal);

	//Copy
	glBufferData(
		GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
		sizeof(float) * n.size(), // tamanho do vector em bytes
		n.data(), // os dados do array associado ao vector
		GL_STATIC_DRAW // indicativo da utilização (estático e para desenho)
	);

// TEXTURES

	//VBO
	glGenBuffers(1, &(this->textures));
	glBindBuffer(GL_ARRAY_BUFFER, this->textures);

	//Copy
	glBufferData(
		GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
		sizeof(float) * t.size(), // tamanho do vector em bytes
		t.data(), // os dados do array associado ao vector
		GL_STATIC_DRAW // indicativo da utilização (estático e para desenho)
	);

}

auto Model::init() -> void {
	//cout << "Initializing model" << endl;
	this->load_file();
	this->load_texture();
	this->prepare_data();
	//cout << "Model initialized" << endl;
}
auto Model::render() -> void {
	//this->color.apply();
	if (this->texture != ""){
		glBindTexture(GL_TEXTURE_2D, this->texture_id);

		glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, this->normal);
		glNormalPointer(GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, this->textures);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, this->vertice_count);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	}
}
