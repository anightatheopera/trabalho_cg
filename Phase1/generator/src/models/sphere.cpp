#include <vector>
#include <cmath>
#define USE_MATH_DEFINES

#include "points.h"

std::vector<Point> draw_sphere(double radius, int slices, int stacks){
 std::vector<Point> points;
    auto staring_point = -radius;
    auto step = (radius*2) / stacks;

    for (int i = 0; i < slices; i++)
    {
        float alpha = ((2 * M_PI) / slices) * i;
        float beta = ((2 * M_PI) / slices) * (i + 1);

        for (int j = 0; j < stacks; j++)
        {       
                auto p1 = Point(radius * sin(alpha) * cos((M_PI/stacks)*j), radius * sin((M_PI/stacks)*j), radius * cos(alpha) * cos((M_PI/stacks)*j));
                auto p2 = Point(radius * sin(beta) * cos((M_PI/stacks)*j), radius * sin((M_PI/stacks)*j), radius * cos(beta) * cos((M_PI/stacks)*j));
                auto p3 = Point(radius * sin(beta) * cos((M_PI/stacks)*(j+1)), radius * sin((M_PI/stacks)*(j+1)), radius * cos(beta) * cos((M_PI/stacks)*(j+1)));
                auto p4 = Point(radius * sin(alpha) * cos((M_PI/stacks)*(j+1)), radius * sin((M_PI/stacks)*(j+1)), radius * cos(alpha) * cos((M_PI/stacks)*(j+1)));
    
                points.push_back(p1);
                points.push_back(p2);
                points.push_back(p3);
                points.push_back(p1);
                points.push_back(p3);
                points.push_back(p4);

                if (j > (stacks/2)){
                    auto p1 = Point(radius * sin(alpha) * cos((M_PI/stacks)*k), -radius * sin((M_PI/stacks)*k), radius * cos(alpha) * cos((M_PI/stacks)*k));
                    auto p2 = Point(radius * sin(beta) * cos((M_PI/stacks)*k), -radius * sin((M_PI/stacks)*k), radius * cos(beta) * cos((M_PI/stacks)*k));
                    auto p3 = Point(radius * sin(beta) * cos((M_PI/stacks)*(k+1)), -radius * sin((M_PI/stacks)*(k+1)), radius * cos(beta) * cos((M_PI/stacks)*(k+1)));
                    auto p4 = Point(radius * sin(alpha) * cos((M_PI/stacks)*(k+1)), -radius * sin((M_PI/stacks)*(k+1)), radius * cos(alpha) * cos((M_PI/stacks)*(k+1)));
                }
        }
    }
    return points;
}
