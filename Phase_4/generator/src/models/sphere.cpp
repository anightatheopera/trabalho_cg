#include <vector>
#include <cmath>
#define USE_MATH_DEFINES

#include "points.h"

std::vector<Point3> draw_sphere(double radius, int slices, int stacks, bool mipmaps){
    std::vector<Point3> return_points;
    std::vector<Point> points;
    std::vector<Point> normal;
    std::vector<Point> texture;
    auto step = (radius*2) / stacks;
    int c_stack = 0;
    int c_slice = 0;

    for (int i = 0; i < slices; i++,c_slice++)
    {
        float alpha = ((2 * M_PI) / slices) * i;
        float beta = ((2 * M_PI) / slices) * (i + 1);

        for (int j = -stacks/2; j < stacks/2; j++,c_stack++){
            auto current_stack = c_stack;
            auto next_stack = c_stack+1;
            auto current_slice = c_slice;
            auto next_slice = c_slice+1;

            auto p1 = Point(radius * sin(alpha) * cos((M_PI/stacks)*j), radius * sin((M_PI/stacks)*j), radius * cos(alpha) * cos((M_PI/stacks)*j));
            auto p2 = Point(radius * sin(beta) * cos((M_PI/stacks)*j), radius * sin((M_PI/stacks)*j), radius * cos(beta) * cos((M_PI/stacks)*j));
            auto p3 = Point(radius * sin(beta) * cos((M_PI/stacks)*(j+1)), radius * sin((M_PI/stacks)*(j+1)), radius * cos(beta) * cos((M_PI/stacks)*(j+1)));
            auto p4 = Point(radius * sin(alpha) * cos((M_PI/stacks)*(j+1)), radius * sin((M_PI/stacks)*(j+1)), radius * cos(alpha) * cos((M_PI/stacks)*(j+1)));

            auto length = sqrt(p1.x*p1.x + p1.y*p1.y + p1.z*p1.z);

            // If we are in the last slice/stack, the next slice/stack is the first one (0)
            if (next_slice > slices)
                next_slice = 0;
            if (next_stack > stacks)
                next_stack = 0;

            auto t1 = Point((float)current_slice / slices, (float)current_stack / stacks, 0);
            auto t2 = Point((float)next_slice / slices, (float)current_stack / stacks, 0);
            auto t3 = Point((float)next_slice / slices, (float)next_stack / stacks, 0);
            auto t4 = Point((float)current_slice / slices, (float)next_stack / stacks, 0);

            if (mipmaps){
                t1 = Point(0,0,0);
                t2 = Point(1,0,0);
                t3 = Point(1,1,0);
                t4 = Point(0,1,0);
            }

            auto n1 = Point(p1.x / length, p1.y / length, p1.z / length);
            auto n2 = Point(p2.x / length, p2.y / length, p2.z / length);
            auto n3 = Point(p3.x / length, p3.y / length, p3.z / length);
            auto n4 = Point(p4.x / length, p4.y / length, p4.z / length);

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
        c_stack = 0;    
    }
    
    // x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty; for each triangle
    for (int i = 0; i < points.size(); i++){
        return_points.push_back(Point3(points[i], normal[i], texture[i]));
    }
    
    return return_points;
}
