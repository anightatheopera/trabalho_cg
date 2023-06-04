#include <vector>
#include <cmath>
#define USE_MATH_DEFINES

#include "points.h"

std::vector<Point3> draw_cone(double radius, double height, int slices, int stacks)
{
    std::vector<Point3> return_points;
    std::vector<Point> points;
    std::vector<Point> normal;
    std::vector<Point> texture;
    auto center_height = 0;
    auto step = height / stacks;
    auto radius_step = radius / stacks;
    auto center_bottom = Point(0, center_height, 0);

    for (int i = 0; i < slices; i++)
    {
        float alpha = ((2 * M_PI) / slices) * i;
        float beta = ((2 * M_PI) / slices) * (i + 1);

        for (int j = 0; j < stacks; j++)
        {
            auto current_stack = j;
            auto next_stack = j+1;
            auto current_slice = i;
            auto next_slice = i+1;

            auto p1 = Point((radius-(radius_step*j)) * sin(alpha), center_height + (step * j), (radius-(radius_step*j)) * cos(alpha));
            auto p2 = Point((radius-(radius_step*j)) * sin(beta), center_height + (step * j), (radius-(radius_step*j)) * cos(beta));
            auto p3 = Point((radius-(radius_step*(j+1))) * sin(beta), center_height + (step * (j + 1)), (radius-(radius_step*(j+1))) * cos(beta));
            auto p4 = Point((radius-(radius_step*(j+1))) * sin(alpha), center_height + (step * (j + 1)), (radius-(radius_step*(j+1))) * cos(alpha));

            if (j == 0)
            {
                points.push_back(center_bottom);
                normal.push_back(Point(0, -1, 0));
                texture.push_back(Point(0.01, 0.01, 0));
                points.push_back(p2);
                normal.push_back(Point(0, -1, 0));
                texture.push_back(Point(0.01, 0, 0));
                points.push_back(p1);
                normal.push_back(Point(0, -1, 0));
                texture.push_back(Point(0, 0, 0));
            }

            auto t1 = Point((float)current_slice / slices, (float)current_stack / stacks, 0);
            auto t2 = Point((float)next_slice / slices, (float)current_stack / stacks, 0);
            auto t3 = Point((float)next_slice / slices, (float)next_stack / stacks, 0);
            auto t4 = Point((float)current_slice / slices, (float)next_stack / stacks, 0);

            auto dist1 = sqrt(pow(p1.x,2)+pow(p1.y-height,2)+pow(p1.y,2)) / (cos(atan(radius/height)));
            auto dist2 = sqrt(pow(p2.x,2)+pow(p2.y-height,2)+pow(p2.y,2)) / (cos(atan(radius/height))); 
            auto dist3 = sqrt(pow(p3.x,2)+pow(p3.y-height,2)+pow(p3.y,2)) / (cos(atan(radius/height))); 
            auto dist4 = sqrt(pow(p4.x,2)+pow(p4.y-height,2)+pow(p4.y,2)) / (cos(atan(radius/height))); 

            auto n1 = Point(p1.x, p1.y - (height - dist1), p1.z);
            auto n2 = Point(p2.x, p2.y - (height - dist2), p2.z);
            auto n3 = Point(p3.x, p3.y - (height - dist3), p3.z);
            auto n4 = Point(p4.x, p4.y - (height - dist4), p4.z);

            n1.normalize();
            n2.normalize();
            n3.normalize();
            n4.normalize();

            points.push_back(p1);
            normal.push_back(n1);
            texture.push_back(t1);
            points.push_back(p2);
            normal.push_back(n2);
            texture.push_back(t2);
            points.push_back(p3);
            normal.push_back(n3);
            texture.push_back(t3);
            points.push_back(p1);
            normal.push_back(n1);
            texture.push_back(t1);
            points.push_back(p3);
            normal.push_back(n3);
            texture.push_back(t3);
            points.push_back(p4);
            normal.push_back(n4);
            texture.push_back(t4);
        }
    }
    
    
    // x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty; for each triangle
    for (int i = 0; i < points.size(); i++){
        return_points.push_back(Point3(points[i], normal[i], texture[i]));
    }
    
    return return_points;
}
