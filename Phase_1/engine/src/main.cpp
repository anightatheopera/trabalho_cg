/*

	Author: Miguel Gomes, Rita Lino, Filipa Gomes, Pedro Pacheco
 Date: 2023-03-08 (YYYY-MM-DD)
 Description: Main file for the engine program
 License: MIT
 Version: 1.0.2
 Changelog:
     1.0.0: Basic rendering implemented
     1.0.1: Camera movement implemented
     1.0.2: Camera parsing implemented with perspective, position, target and up vectors

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

using namespace tinyxml2;
using namespace std;

// Global variables
vector<Model> models;
Camera camera;

vector<int> modes = {GL_FILL, GL_LINE, GL_POINT};
int mode = 1;



void process_special_keys(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_LEFT : 
			camera.angle_z -= 0.1f;
			break;
		case GLUT_KEY_RIGHT : 
			camera.angle_z += 0.1f;
			break;
		case GLUT_KEY_UP : 
			camera.angle_y += 0.1f;
			break;
		case GLUT_KEY_DOWN : 
			camera.angle_y -= 0.1f;
			break;
	}
	camera.update();
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
		camera.radius_camera += 0.1;
		camera.update();
		break;
	    case '+':
		camera.radius_camera -= 0.1;
		camera.update();
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
	if (camera.screen_height == 0)
		camera.screen_height = 1;
	// compute window's aspect ratio
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set perspective
	camera.render_persepective();

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

	camera.look_at();
	
	draw_axis();
		
	// put drawing instructions here
	for (auto model: models){
		// put model transformations here
		glColor3f((float)219/255, (float)112/255, (float)147/255);

		// put model drawing instructions here
		glBegin(GL_TRIANGLES);
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

auto parse_camera(XMLElement* camera_element, int screen_width, int screen_height){
	if (camera_element == NULL) throw runtime_error("Camera element not found");
	camera_element = camera_element->FirstChildElement("position");
	if (camera_element == NULL) throw runtime_error("Camera position element not found");
	auto position = Point(stod(camera_element->Attribute("x")), stod(camera_element->Attribute("y")),stod(camera_element->Attribute("z")));
	camera_element = camera_element->NextSiblingElement("lookAt");
	if (camera_element == NULL) throw runtime_error("Camera lookAt element not found");
	auto lookAt = Point(stod(camera_element->Attribute("x")), stod(camera_element->Attribute("y")),stod(camera_element->Attribute("z")));
	camera_element = camera_element->NextSiblingElement("up");
	if (camera_element == NULL) throw runtime_error("Camera up element not found");
	auto up = Point(stod(camera_element->Attribute("x")), stod(camera_element->Attribute("y")),stod(camera_element->Attribute("z")));
	camera_element = camera_element->NextSiblingElement("projection");
	if (camera_element == NULL) throw runtime_error("Camera projection element not found");
	auto perspective = Point(stod(camera_element->Attribute("fov")),stod(camera_element->Attribute("near")), stod(camera_element->Attribute("far")));

	camera = Camera(position, lookAt, up, perspective, screen_width, screen_height);
}


auto parse_models(XMLElement* models_element){
	vector<string> model_files;
	if (models_element == nullptr) throw runtime_error("Error finding element _ models _");
	models_element = models_element->FirstChildElement("model");
	if (models_element == nullptr) throw runtime_error("Error finding element _ model _");
	while (models_element != nullptr){
		model_files.push_back(models_element->Attribute("file"));
		models_element = models_element->NextSiblingElement("model");
	}
	return model_files;
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

		auto window = root->FirstChildElement("window");
		auto screen_width = stoi(window->Attribute("width"));
		auto screen_height = stoi(window->Attribute("height"));
		auto camera_element = root->FirstChildElement("camera");
		if (camera_element == nullptr) throw runtime_error("Error finding element _ camera _");

		parse_camera(camera_element, screen_width, screen_height);

		XMLElement* models_element = root->FirstChildElement("group")->FirstChildElement("models");
		if (models_element == nullptr) throw runtime_error("Error finding element _ models _");
		
		files = parse_models(models_element);
		
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	for (auto file : files){
		models.push_back(Model(file,load_from_file(file)));
	}

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(camera.screen_width,camera.screen_height);
	glutCreateWindow("CG@DI-UM");
	glPolygonMode(GL_FRONT_AND_BACK, modes[1]);
		
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
