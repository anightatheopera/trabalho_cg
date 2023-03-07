#include <vector>
#include <cmath>
#define USE_MATH_DEFINES

#include "points.h"

std::vector<Point> draw_cone(double radius, double height, int slices, int stacks)
{
    std::vector<Point> points;
    auto staring_point = 0;
    auto step = height / stacks;
    auto radius_step = radius / stacks;
    auto center_bottom = Point(0, staring_point, 0);

    for (int i = 0; i < slices; i++)
    {
        float alpha = ((2 * M_PI) / slices) * i;
        float beta = ((2 * M_PI) / slices) * (i + 1);

        for (int j = 0; j < stacks; j++)
        {

            auto p1 = Point((radius-(radius_step*j)) * sin(alpha), staring_point + (step * j), (radius-(radius_step*j)) * cos(alpha));
            auto p2 = Point((radius-(radius_step*j)) * sin(beta), staring_point + (step * j), (radius-(radius_step*j)) * cos(beta));
            auto p3 = Point((radius-(radius_step*(j+1))) * sin(beta), staring_point + (step * (j + 1)), (radius-(radius_step*(j+1))) * cos(beta));
            auto p4 = Point((radius-(radius_step*(j+1))) * sin(alpha), staring_point + (step * (j + 1)), (radius-(radius_step*(j+1))) * cos(alpha));

            if (j == 0)
            {
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
