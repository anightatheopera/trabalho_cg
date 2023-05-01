// Purpose: Header file for Point class
#ifndef POINT_H
#define POINT_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

class Point {
    public:
        float x;
        float y;
        float z;

        Point();

        Point(float x, float y, float z);

        float getX();
        float getY();
        float getZ();

	void setX(float x);
	void setY(float y);
	void setZ(float z);

};

#endif
