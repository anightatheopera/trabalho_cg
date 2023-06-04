#include <vector>
#include <math.h>
#include <ostream>
#include <iostream>

#define _USE_MATH_DEFINES

#include "points.h"

std::vector<Point3> draw_torus(double inner_radius, double outer_radius, int slices, int stacks){
    std::vector<Point3> return_points;
    std::vector<Point> points;
    std::vector<Point> normals;
    std::vector<Point> texture;

    double donut_radius = (inner_radius + outer_radius)/2;
    double girth_radius = donut_radius-inner_radius;

    double p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z, p4x, p4y, p4z;

    double slices_delta = (2*M_PI)/slices; //angle between slices       theta
    double stacks_delta = (2*M_PI)/stacks; //angle between stacks       phi

    for (int i = 0; i < stacks; i++){
        for (int j = 0; j < slices; j++){

            auto stack_current = i;
            auto stack_next = i+1;
            auto slice_current = j;
            auto slice_next = j+1; 

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

            auto normal_1 = normal(Point(p1x, p1y, p1z), Point(p2x, p2y, p2z), Point(p4x, p4y, p4z));
            auto normal_2 = normal(Point(p2x, p2y, p2z), Point(p3x, p3y, p3z), Point(p4x, p4y, p4z));

            auto t1 = Point((float)slice_current/slices, (float)stack_current/stacks, 0);
            auto t2 = Point((float)slice_current/slices, (float)stack_next/stacks, 0);
            auto t3 = Point((float)slice_next/slices, (float)stack_next/stacks, 0);
            auto t4 = Point((float)slice_next/slices, (float)stack_current/stacks, 0);            

            //push them to points vector in the form of a point in order to be able to draw them
            points.push_back(Point(p1x, p1y, p1z));
            normals.push_back(normal_1);
            texture.push_back(t1);
            points.push_back(Point(p2x, p2y, p2z));
            normals.push_back(normal_1);
            texture.push_back(t2);
            points.push_back(Point(p4x, p4y, p4z));
            normals.push_back(normal_1);
            texture.push_back(t4);
            
            points.push_back(Point(p2x, p2y, p2z));
            normals.push_back(normal_2);
            texture.push_back(t2);
            points.push_back(Point(p3x, p3y, p3z));
            normals.push_back(normal_2);
            texture.push_back(t3);
            points.push_back(Point(p4x, p4y, p4z));
            normals.push_back(normal_2);
            texture.push_back(t4);
        }
    }

    // x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty; for each triangle
    for (int i = 0; i < points.size(); i++){
        return_points.push_back(Point3(points[i], normals[i], texture[i]));
    }
    
    return return_points;
}