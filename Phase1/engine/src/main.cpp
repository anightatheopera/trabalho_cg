// CG Engine
//
//

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

using namespace tinyxml2;
using namespace std;

struct Model {
	string name;
	vector<Point> points;
	//Color;
	//Texture;
	//Material;
	//Transformations;
	//Animation;
	//Light;
};

// Global variables
int width = 800, height = 800;
vector<Model> models;

vector<int> modes = {GL_FILL, GL_LINE, GL_POINT};
int mode = 0;

void handle_key(unsigned char key, int x, int y) {
    switch (key) {
	    case 'm':
	    case 'M':
	        mode = (mode + 1) % modes.size();
	        glPolygonMode(GL_FRONT_AND_BACK, modes[mode]);
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
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
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
		gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	
	draw_axis();
		
	// put drawing instructions here
	for (auto model: models){
		// put model transformations here
		

		// put model drawing instructions here
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);
		for (auto point: model.points){
			glVertex3d(point.x, point.y, point.z);
		}
		glEnd();
	}
	
	// End of frame
	glutSwapBuffers();
}



vector<string> split (const string &s, char delim) {
	vector<std::string> result;
    	stringstream ss(s);
    	string item;

    	while (getline (ss, item, delim)) {
        	result.push_back (item);
	}

    	return result;
}



vector<Point> load_from_file(string filename){
	ifstream file(filename);
	vector<Point> points;
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
			points.push_back(p);
		}
	}
	file.close();
	return points;
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
        	XMLDocument xml_doc;

        	XMLError eResult = xml_doc.LoadFile(filename);
        	if (eResult != XML_SUCCESS) throw runtime_error("Error loading file");

        	XMLNode* root = xml_doc.FirstChildElement("world");
        	if (root == nullptr) throw runtime_error("Error finding root _ world _");
        
		XMLElement* element = root->FirstChildElement("group");
		if (element == nullptr) throw runtime_error("Error finding element _ group _");
		
		element = element->FirstChildElement("models");
		if (element == nullptr) throw runtime_error("Error finding element _ models _");
		element = element->FirstChildElement("model");
		if (element == nullptr) throw runtime_error("Error finding element _ model _");

		while (element != nullptr){
			files.push_back(element->Attribute("file"));
			element = element->NextSiblingElement("model");
		}
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	for (auto file : files){
		Model model;
		model.name = file;
		model.points = load_from_file(file);
		models.push_back(model);
	}

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(handle_key);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();

       return 0;
}
