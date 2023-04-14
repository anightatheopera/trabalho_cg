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

#include "scene.h"
#include "camera.h"


unsigned char picking(int x, int y, Scene scene) {
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	scene.camera.look_at();
	glDepthFunc(GL_LEQUAL);
	scene.render(true);
	glDepthFunc(GL_LESS);
	unsigned char res[4];
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, res);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	// return index of the object in the scene
	return res[0];
}

void render_hover_text(const std::string& text , int x, int y , Camera camera) {
	// Guardar a projeção anterior
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	// Projecção ortogonal para que as coordenadas de desenho coincidam com o tamanho da
	gluOrtho2D(0, camera.screen_width, camera.screen_height, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	void* font = GLUT_BITMAP_HELVETICA_18;
	// Centrar o texto, calculando a dimensão da mensagem em pixeis
	float textw = glutBitmapLength(font, (unsigned char*) text.c_str());
	glRasterPos2d(x, y); // text position in pixels
	// Ignorar profundidade
	glDisable(GL_DEPTH_TEST);
	// Desenhar a mensagem, caracter a caracter
	for (char c : text)
	{
	glutBitmapCharacter(font, c);
	}
	// Restaurar as matrizes anteriores
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}
