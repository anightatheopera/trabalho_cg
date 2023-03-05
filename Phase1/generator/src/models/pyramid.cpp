#include <vector>
#include <cmath>
#define USE_MATH_DEFINES

#include "points.h"

std::vector<Point> draw_pyramid(double base, double height, int stacks){
    std::vector<Point> points;
    auto staring_point = -height / 2;
    auto step = height / stacks;
    auto base_step = base / stacks;
    auto center_bottom = Point(0, staring_point, 0);
    auto center_top = Point(0, staring_point + height, 0);


    for (int j = 0; j < stacks; j++)
    {
        auto p1 = Point((base-(base_step*j)) * sin(0), staring_point + (step * j), (base-(base_step*j)) * cos(0)); // 
        auto p2 = Point((base-(base_step*j)) * sin(M_PI/2), staring_point + (step * j), (base-(base_step*j)) * cos(M_PI/2));
        auto p3 = Point((base-(base_step*j)) * sin(M_PI), staring_point + (step * j), (base-(base_step*j)) * cos(M_PI));
        auto p4 = Point((base-(base_step*j)) * sin(3*M_PI/2), staring_point + (step * j), (base-(base_step*j)) * cos(3*M_PI/2));

        auto p5 = Point((base-(base_step*(j+1))) * sin(0), staring_point + (step * (j+1)), (base-(base_step*(j+1))) * cos(0));
        auto p6 = Point((base-(base_step*(j+1))) * sin(M_PI/2), staring_point + (step * (j+1)), (base-(base_step*(j+1))) * cos(M_PI/2));
        auto p7 = Point((base-(base_step*(j+1))) * sin(M_PI), staring_point + (step * (j+1)), (base-(base_step*(j+1))) * cos(M_PI));
        auto p8 = Point((base-(base_step*(j+1))) * sin(3*M_PI/2), staring_point + (step * (j+1)), (base-(base_step*(j+1))) * cos(3*M_PI/2));

        if (j == 0)
        {
            points.push_back(center_bottom);
            points.push_back(p2);
            points.push_back(p1);
        }

        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p5);
        points.push_back(p2);
        points.push_back(p6);
        points.push_back(p5);
        points.push_back(p2);
        points.push_back(p3);
        points.push_back(p6);
        points.push_back(p3);
        points.push_back(p7);
        points.push_back(p6);
        points.push_back(p3);
        points.push_back(p4);
        points.push_back(p7);
        points.push_back(p4);
        points.push_back(p8);
        points.push_back(p7);
        points.push_back(p4);
        points.push_back(p1);
        points.push_back(p8);
        points.push_back(p1);
        points.push_back(p5);
        points.push_back(p8);

    }

    return points;
}