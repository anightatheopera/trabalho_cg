#include <vector>
#include <math.h>

#define _USE_MATH_DEFINES

#include "points.h"

std::vector<Point> draw_torus(double inner_radius, double outer_radius, int slices, int stacks){
    std::vector<Point> points;

    double slices_delta = (2*M_PI)/slices; //angle between slices
    double stacks_delta = (2*M_PI)/stacks; //angle between stacks

    for (int i = 0; i < slices; i++){
        for (int j = 0; j < stacks; j++){
            //calculate x, y, z coordinates

            //push them to points vector in the form of a point in order to be able to draw them
        }
    }
    return points;
}