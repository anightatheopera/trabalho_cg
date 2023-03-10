#include <vector>
#include <math.h>

#define _USE_MATH_DEFINES

#include "points.h"

std::vector<Point> draw_torus(double inner_radius, double outer_radius, int slices, int stacks){
    std::vector<Point> points;

    double donut_radius = (inner_radius + outer_radius)/2;
    double girth_radius = donut_radius-inner_radius;

    double p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z, p4x, p4y, p4z;

    double slices_delta = (2*M_PI)/slices; //angle between slices       theta
    double stacks_delta = (2*M_PI)/stacks; //angle between stacks       phi

    for (int i = 0; i < stacks; i++){
        for (int j = 0; j < slices; j++){
            //calculate x, y, z coordinates
            p1x = (donut_radius + girth_radius * cos(stacks_delta*i))*cos(slices_delta*j);
            p1y = girth_radius*sin(stacks_delta*i);
            p1z = (donut_radius + girth_radius *cos(stacks_delta*i))*sin(slices_delta*j);
            
            p2x = (donut_radius + girth_radius * cos(stacks_delta*(i+1)))*cos(slices_delta*j);
            p2y = girth_radius*sin(stacks_delta*(i+1));
            p2z = (donut_radius + girth_radius *cos(stacks_delta*(i+1)))*sin(slices_delta*j);

            p3x = (donut_radius + girth_radius * cos(stacks_delta*(i+1)))*cos(slices_delta*(j+1));
            p3y = girth_radius*sin(stacks_delta*(i+1));
            p3z = (donut_radius + girth_radius *cos(stacks_delta*(i+1)))*sin(slices_delta*(j+1));

            p4x = (donut_radius + girth_radius * cos(stacks_delta*(i)))*cos(slices_delta*(j+1));
            p4y = girth_radius*sin(stacks_delta*i);
            p4z = (donut_radius + girth_radius *cos(stacks_delta*i))*sin(slices_delta*(j+1));

            //push them to points vector in the form of a point in order to be able to draw them
            points.push_back(Point(p1x, p1y, p1z));
            points.push_back(Point(p2x, p2y, p2z));
            points.push_back(Point(p4x, p4y, p4z));

            points.push_back(Point(p2x, p2y, p2z));
            points.push_back(Point(p3x, p3y, p3z));
            points.push_back(Point(p4x, p4y, p4z));
        }
    }
    return points;
}