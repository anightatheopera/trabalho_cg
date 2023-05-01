// Purpose: Header file for transformation.cpp
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <string>

#include "points.h"

enum class TransformationType {
    None,
    Translate,
    Rotate,
    Scale
};
//TransformationType col = TransformationType::Rotate;

class Transformation {
    public:
        TransformationType type;
        int angle;
        float x;
        float y;
        float z;

        Transformation(TransformationType type, float x, float y, float z, int angle);
        Transformation();

	auto show() -> std::string;

        void apply();
};

#endif
