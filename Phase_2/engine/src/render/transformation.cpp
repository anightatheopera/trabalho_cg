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
#include <expat.h>

#include "transformation.h"

Transformation::Transformation(TransformationType type, float x, float y, float z, int angle) {
    this->type = type;
    this->x = x;
    this->y = y;
    this->z = z;
    this->angle = angle;
}

Transformation::Transformation() {
    this->type = TransformationType::None;
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->angle = 0;
}

void Transformation::apply() {
    switch (this->type)
    {
        case TransformationType::Translate:
            glTranslatef(this->x, this->y, this->z);
            //std::cout << "Translate: " << this->x << " " << this->y << " " << this->z << std::endl;
            break;
        case TransformationType::Rotate:
            glRotatef(this->angle, this->x, this->y, this->z);
            //std::cout << "Rotate: " << this->angle << " " << this->x << " " << this->y << " " << this->z << std::endl;
            break;
        case TransformationType::Scale:
            glScalef(this->x, this->y, this->z);
            //std::cout << "Scale: " << this->x << " " << this->y << " " << this->z << std::endl;
            break;
        default:
            break;
    }
}

