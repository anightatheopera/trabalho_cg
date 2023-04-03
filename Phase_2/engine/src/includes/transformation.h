#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

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

        void apply();
};

#endif