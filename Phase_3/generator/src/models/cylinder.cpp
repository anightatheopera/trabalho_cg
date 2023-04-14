#include <vector>
#include <cmath>
#define USE_MATH_DEFINES

#include "points.h"

std::vector<Point> draw_cylinder(double radius, double height, int slices, int stacks){
    std::vector<Point> points;
    auto staring_point = -height/2;
    auto step = height/stacks;
    auto center_bottom = Point(0,staring_point,0);
    auto center_top = Point(0,staring_point+height,0);

    for (int i = 0; i < slices; i++) {
		float alpha = ((2*M_PI)/slices)*i;
		float beta = ((2*M_PI)/slices)*(i+1);

        for (int j=0; j < stacks; j++){

            auto p1 = Point(radius*sin(alpha),staring_point+(step*j),radius*cos(alpha));
            auto p2 = Point(radius*sin(beta),staring_point+(step*j),radius*cos(beta));
            auto p3 = Point(radius*sin(beta),staring_point+(step*(j+1)),radius*cos(beta));
            auto p4 = Point(radius*sin(alpha),staring_point+(step*(j+1)),radius*cos(alpha));
            
            if (j == stacks-1){
                points.push_back(p4);
                points.push_back(p3);
                points.push_back(center_top);
            }

            if (j == 0){
                points.push_back(center_bottom);
                points.push_back(p2);
                points.push_back(p1);

            }

            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);
            points.push_back(p1);
            points.push_back(p3);
            points.push_back(p4);
        }
	}


    return points;
}