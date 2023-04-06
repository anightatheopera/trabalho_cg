/*

	Author: Miguel Gomes, Rita Lino, Filipa Gomes, Pedro Pacheco
 Date: 2023-03-08 (YYYY-MM-DD)
 Description: Main file for the engine program
 License: MIT
 Version: 2.0.1
 Changelog:
     1.0.0: Basic rendering implemented
     1.0.1: Camera movement implemented
     1.0.2: Camera parsing implemented with perspective, position, target and up vectors
	 2.0.0: Phase 2 of the project
	 2.0.1: Added transformations to the engine

 Engine <Scene>

*/

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


#include "tinyxml2.h"
#include "points.h"
#include "model.h"
#include "camera.h"
#include "transformation.h"
#include "group.h"
#include "scene.h"
#include "parser.h"
#include "colorf.h"

using namespace tinyxml2;
using namespace std;

// Global variables
Scene scene;

vector<int> modes = {GL_FILL, GL_LINE, GL_POINT};
int mode = 1;

void process_special_keys(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_LEFT : 
			scene.camera.angle_z -= 0.1f;
			break;
		case GLUT_KEY_RIGHT : 
			scene.camera.angle_z += 0.1f;
			break;
		case GLUT_KEY_UP : 
			scene.camera.angle_y += 0.1f;
			break;
		case GLUT_KEY_DOWN : 
			scene.camera.angle_y -= 0.1f;
			break;
	}
	scene.camera.update();
	glutPostRedisplay();

}

void process_normal_keys(unsigned char key, int x, int y) {
    switch (key) {
	    case 'm':
	    case 'M':
	        mode = (mode + 1) % modes.size();
	        glPolygonMode(GL_FRONT_AND_BACK, modes[mode]);
	        break;
	    case '-':
		scene.camera.radius_camera += 0.1;
		scene.camera.update();
		break;
	    case '+':
		scene.camera.radius_camera -= 0.1;
		scene.camera.update();
		break;
	// Exit because bspwm has no min, max or close buttons
	    case 'q':
	    case 'Q':
	    	exit(0);
	default:
	    break;
    }
    glutPostRedisplay();
}



void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can't make a window with zero width).
	if (scene.camera.screen_height == 0)
		scene.camera.screen_height = 1;
	// compute window's aspect ratio
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set perspective
	scene.camera.render_persepective();

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void draw_axis(){
	glBegin(GL_LINES);
    		//X axis in Red
    		glColor3f(1.0f, 0.0f, 0.0f);
    		glVertex3f( 0.0f, 0.0f, 0.0f);
    		glVertex3f( 1.0f, 0.0f, 0.0f);
    		//Y Axis in Green
    		glColor3f(0.0f, 1.0f, 0.0f);
    		glVertex3f(0.0f, 0.0f, 0.0f);
    		glVertex3f(0.0f, 1.0f, 0.0f);
    		//Z Axis in Blue
    		glColor3f(0.0f, 0.0f, 1.0f);
    		glVertex3f(0.0f, 0.0f, 0.0f);
    		glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();    
}

																																																																																																				
void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// set camera
	glLoadIdentity();

	scene.camera.look_at();
	
	draw_axis();

	scene.render();
	
	// End of frame
	glutSwapBuffers();
}

int main(int argc, char **argv){

	// get xml file from command line
	if (argc < 2){
		cout << "Usage: " << argv[0] << " <xml_file>" << endl;
		return 1;
	}
	const char* filename = argv[1];

	vector<string> files;

	try {
		Parser parser = Parser(filename);
		scene = parser.parse();

	} catch (exception& e) {
		cout << e.what() << endl;
	}

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(scene.camera.screen_width,scene.camera.screen_height);
	glutCreateWindow("CG@DI-UM");
	glPolygonMode(GL_FRONT_AND_BACK, modes[1]);

	scene.load_models();
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(process_normal_keys);
	glutSpecialFunc(process_special_keys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();

       return 0;
}

