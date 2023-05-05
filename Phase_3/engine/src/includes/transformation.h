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
#include "curve.h"

enum class TransformationType {
    None,
    TimedTranslate,
    Translate,
    TimedRotate,
    Rotate,
    TimedScale,
    Scale
};
//TransformationType col = TransformationType::Rotate;

class Transformation {
    public:
        TransformationType type;
        float time;
        int angle;
        float x;
        float y;
        float z;
        bool align;
	Curve curve;

        Transformation(TransformationType type, float x, float y, float z, int angle, float time, bool align, Curve curve); // all
															    //
        Transformation(TransformationType type, float x, float y, float z, int angle); // rotate
        Transformation(TransformationType type, float x, float y, float z, float time); // rotate, scale (timed)
												   //
        Transformation(TransformationType type, float x, float y, float z); // translate, scale
        Transformation(TransformationType type, float time, bool align, Curve curve); // translate (timed)
												    //
        Transformation();

	auto show() -> std::string;

        void apply(bool lines = false);
	void render_catmullrom_curve();
};

#endif
