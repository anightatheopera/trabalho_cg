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
#include <cmath>

#include "points.h"
#include "camera.h"


using namespace std;

Camera::Camera(Point _position, Point _target, Point _up, Point _perspective, int _screen_width, int _screen_height){
    position = _position;
    target = _target;
    up = _up;
    perspective = _perspective;
    angle_y = atan(position.x/position.z);
    angle_z = atan(position.y/position.x);
    radius_camera = sqrt(pow(position.x, 2) + pow(position.y, 2) + pow(position.z, 2));
    screen_width = _screen_width;
    screen_height = _screen_height;
}

auto Camera::show_values() -> void{
    cout << "Position: " << position.x << " " << position.y << " " << position.z << endl;
    cout << "Target: " << target.x << " " << target.y << " " << target.z << endl;
    cout << "Up: " << up.x << " " << up.y << " " << up.z << endl;
    cout << "Perspective: " << perspective.x << " " << perspective.y << " " << perspective.z << endl;
    cout << "Angle_y: " << angle_y << endl;
    cout << "Angle_z: " << angle_z << endl;
    cout << "Radius: " << radius_camera << endl;
    cout << "Screen width: " << screen_width << endl;
    cout << "Screen height: " << screen_height << endl;
}

Camera::Camera(){
    position = Point(5, 3, 5);
    target = Point(0, 0, 0);
    up = Point(0, 1, 0);
    perspective = Point(60, 1, 1000);
    angle_y = atan(position.x/position.z);
    angle_z = atan(position.y/position.x);
    radius_camera = sqrt(pow(position.x, 2) + pow(position.y, 2) + pow(position.z, 2));
    screen_width = 800;
    screen_height = 600;

}

auto Camera::render_persepective() -> void {
    gluPerspective(perspective.getX(), screen_width * 1.0f / screen_height, perspective.getY(), perspective.getZ());
}

auto Camera::look_at() -> void {
	this->show_values();
	cout << "X " << radius_camera*cos(angle_y)*sin(angle_z) + position.x << "Y " <<(radius_camera*sin(angle_y)) + position.y << "Z " << (radius_camera*cos(angle_y)*cos(angle_z)) + position.z << endl;
    gluLookAt((radius_camera*cos(angle_y)*sin(angle_z)) + position.x,(radius_camera*sin(angle_y)) + position.y,(radius_camera*cos(angle_y)*cos(angle_z)) + position.z,
            target.x,target.y,target.z,
            up.x,up.y,up.z);
}





