#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define TESSELATION 100
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <expat.h>

#include "transformation.h"

using namespace std;


auto get_delta() -> int {
    static int prev_elapsed = 0;

    auto curr_elapsed = glutGet(GLUT_ELAPSED_TIME);
    auto delta = curr_elapsed - prev_elapsed;
    prev_elapsed = curr_elapsed;

    return delta;
}

Transformation::Transformation(TransformationType type, float x, float y, float z, int angle, float time, bool align, Curve curve) {
    this->type = type;
    this->x = x;
    this->y = y;
    this->z = z;
    this->angle = angle;
    this->time = time;
    this->align = align;
    this->curve = curve;
}

//Rotate
Transformation::Transformation(TransformationType type, float x, float y, float z, int angle) {
    this->type = type;
    this->x = x;
    this->y = y;
    this->z = z;
    this->angle = angle;
    this->time = 0;
    this->align = false;
    this->curve = Curve();
}

//Rotate, Scale (timed)
Transformation::Transformation(TransformationType type, float x, float y, float z, float time) {
    this->type = type;
    this->x = x;
    this->y = y;
    this->z = z;
    this->angle = 0;
    this->time = time;
    this->align = false;
    this->curve = Curve();
}

//Translate, Scale
Transformation::Transformation(TransformationType type, float x, float y, float z) {
    this->type = type;
    this->x = x;
    this->y = y;
    this->z = z;
    this->angle = 0;
    this->time = 0;
    this->align = false;
    this->curve = Curve();
}

//Translate (timed)
Transformation::Transformation(TransformationType type, float time, bool align, Curve curve) {
    this->type = type;
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->angle = 0;
    this->time = time;
    this->align = align;
    this->curve = curve;
}

Transformation::Transformation() {
    this->type = TransformationType::None;
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->angle = 0;
    this->time = 0;
    this->align = false;
    this->curve = Curve();
}

auto Transformation::show() -> std::string {
	std::stringstream ss;
    switch (this->type) {
	case TransformationType::None:
	    ss << "None";
	    break;
	case TransformationType::Translate:
	    ss << "Translate " << this->x << " " << this->y << " " << this->z;
	    break;
	case TransformationType::Scale:
	    ss << "Scale " << this->x << " " << this->y << " " << this->z;
	    break;
	case TransformationType::Rotate:
	    ss << "Rotate " << this->x << " " << this->y << " " << this->z << " " << this->angle;
	    break;
    case TransformationType::TimedTranslate:
        ss << "TimedTranslate " << this->x << " " << this->y << " " << this->z << " " << this->time;
        break;
    case TransformationType::TimedScale:
        ss << "TimedScale " << this->x << " " << this->y << " " << this->z << " " << this->time;
        break;
    case TransformationType::TimedRotate:
        ss << "TimedRotate " << this->x << " " << this->y << " " << this->z << " " << this->angle << " " << this->time;
        break;
    }
    return ss.str();
}

void Transformation::apply() {
	float time = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    switch (this->type)
        {
        case TransformationType::Translate:{
            glTranslatef(this->x, this->y, this->z);
            //std::cout << "Translate: " << this->x << " " << this->y << " " << this->z << std::endl;
            break;
        }
        case TransformationType::Rotate:{
            glRotatef(this->angle, this->x, this->y, this->z);
            //std::cout << "Rotate: " << this->angle << " " << this->x << " " << this->y << " " << this->z << std::endl;
            break;
        }
        case TransformationType::Scale:{
            glScalef(this->x, this->y, this->z);
            //std::cout << "Scale: " << this->x << " " << this->y << " " << this->z << std::endl;
            break;
        }
        case TransformationType::TimedTranslate:{

            // Ficha 9, Catmull-Rom Curves Solução
		    float t = (time / this->time);
            //this->render_catmullrom_curve();
            this->curve.get_global_catmullrom(t);
            Point pos = this->curve.get_position();
            Point deriv = this->curve.get_derivated();
            glTranslatef(pos.x, pos.y, pos.z);

            // algo aqui não está certo, o alinhamento não está a funcionar ele está de pernas para o ar
            if (this->align) {

                float x[3] = {deriv.x, deriv.y, deriv.z};
                normalize(x);
                
                float z[3];
                float prev_y[3] = {this->curve.get_previous_y().x, this->curve.get_previous_y().y, this->curve.get_previous_y().z};
                cross(x, prev_y, z);
                normalize(z);
                
                float y[3];
                cross(z, x, y);
                normalize(y);
                
                this->curve.set_previous_y(Point(y[0], y[1], y[2]));

                float m[16];
                build_rotmatrix(x, y, z, m);

                glMultMatrixf(m);
            }
            break;
        }
        case TransformationType::TimedRotate:{
            float angle = 360.0 / this->time * time;
            while (angle > 360.0) angle -= 360.0;
            glRotatef(angle, this->x, this->y, this->z);
            break;
        }
        case TransformationType::TimedScale:{
            float scale = 1 - (time / this->time) < 0 ? 1 : (time / this->time);

            glScalef(this->x * scale, this->y * scale, this->z * scale);
            break;
        }
        default:
            break;
    }
}

void Transformation::render_catmullrom_curve() {
	if (this->curve.get_control_points_count() < 4) {
		return;
	}
	else {
        
		glBegin(GL_LINE_LOOP);
		for (float gt = 0; gt < 1; ) {
			this->curve.get_global_catmullrom(gt);
			Point p = this->curve.get_position();
			glVertex3f(p.x, p.y, p.z);
			gt += 1.0f / TESSELATION;
		}
		glEnd();
	}
}







