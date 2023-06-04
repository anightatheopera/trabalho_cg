#include <vector>
#include <cmath>
#define USE_MATH_DEFINES

#include "points.h"

std::vector<Point3> draw_pyramid(double base, double height, int stacks){
    std::vector<Point3> return_points;
    std::vector<Point> points;
    std::vector<Point> normals;
    std::vector<Point> texture;
    auto staring_point = -height / 2;
    auto step = height / stacks;
    auto base_step = base / stacks;
    auto center_bottom = Point(0, staring_point, 0);
    auto center_top = Point(0, staring_point + height, 0);

    float texture_step = 1.0 / stacks;
    float texture_starting_point = 0.0;

    for (int j = 0; j < stacks; j++)
    {

        auto texture_now = texture_starting_point + (texture_step * j);
        auto texture_next = texture_starting_point + (texture_step * (j+1));
        // Base to Top construction

        auto p1 = Point((base-(base_step*j)) * sin(0), staring_point + (step * j), (base-(base_step*j)) * cos(0)); // 
        auto p2 = Point((base-(base_step*j)) * sin(M_PI/2), staring_point + (step * j), (base-(base_step*j)) * cos(M_PI/2));
        auto p3 = Point((base-(base_step*j)) * sin(M_PI), staring_point + (step * j), (base-(base_step*j)) * cos(M_PI));
        auto p4 = Point((base-(base_step*j)) * sin(3*M_PI/2), staring_point + (step * j), (base-(base_step*j)) * cos(3*M_PI/2));

        auto p5 = Point((base-(base_step*(j+1))) * sin(0), staring_point + (step * (j+1)), (base-(base_step*(j+1))) * cos(0));
        auto p6 = Point((base-(base_step*(j+1))) * sin(M_PI/2), staring_point + (step * (j+1)), (base-(base_step*(j+1))) * cos(M_PI/2));
        auto p7 = Point((base-(base_step*(j+1))) * sin(M_PI), staring_point + (step * (j+1)), (base-(base_step*(j+1))) * cos(M_PI));
        auto p8 = Point((base-(base_step*(j+1))) * sin(3*M_PI/2), staring_point + (step * (j+1)), (base-(base_step*(j+1))) * cos(3*M_PI/2));

        auto n_front = normal(p1, p2, p5);
        auto n_back = normal(p3, p4, p7);
        auto n_left = normal(p1, p4, p5);
        auto n_right = normal(p2, p3, p6);
        auto n_bottom = normal(p1, p2, p3);

        if (j == 0)
        {
            points.push_back(center_bottom);
            normals.push_back(n_bottom);
            texture.push_back(Point(0.5,0.5, 0));
            
            points.push_back(p2);
            normals.push_back(n_bottom);
            texture.push_back(Point(1, 0, 0));
            
            points.push_back(p1);
            normals.push_back(n_bottom);
            texture.push_back(Point(0, 0, 0));
            
            points.push_back(center_bottom);
            normals.push_back(n_bottom);
            texture.push_back(Point(0.5,0.5, 0));
            
            points.push_back(p3);
            normals.push_back(n_bottom);
            texture.push_back(Point(1, 1, 0));
            
            points.push_back(p2);
            normals.push_back(n_bottom);
            texture.push_back(Point(0, 0, 0));
            
            points.push_back(center_bottom);
            normals.push_back(n_bottom);
            texture.push_back(Point(0.5,0.5, 0));
            
            points.push_back(p4);
            normals.push_back(n_bottom);
            texture.push_back(Point(0, 1, 0));
            
            points.push_back(p3);
            normals.push_back(n_bottom);
            texture.push_back(Point(1, 1, 0));
            
            points.push_back(center_bottom);
            normals.push_back(n_bottom);
            texture.push_back(Point(0.5,0.5, 0));
            
            points.push_back(p1);
            normals.push_back(n_bottom);
            texture.push_back(Point(0, 0, 0));
            
            points.push_back(p4);
            normals.push_back(n_bottom);
            texture.push_back(Point(0, 1, 0));
        }
        auto t1 = Point(0, texture_now, 0);
        auto t2 = Point(1, texture_now, 0);
        auto t3 = Point(1, texture_next, 0);
        auto t4 = Point(0, texture_next, 0);

        // front
        points.push_back(p1);
        normals.push_back(n_front);
        texture.push_back(t1);
        
        points.push_back(p2);
        normals.push_back(n_front);
        texture.push_back(t2);
        
        points.push_back(p5);
        normals.push_back(n_front);
        texture.push_back(t4);
        
        points.push_back(p2);
        normals.push_back(n_front);
        texture.push_back(t2);
        
        points.push_back(p6);
        normals.push_back(n_front);
        texture.push_back(t3);
        
        points.push_back(p5);
        normals.push_back(n_front);
        texture.push_back(t4);

        // Right
        points.push_back(p2);
        normals.push_back(n_right);
        texture.push_back(t1);
        
        points.push_back(p3);
        normals.push_back(n_right);
        texture.push_back(t2);
        
        points.push_back(p6);
        normals.push_back(n_right);
        texture.push_back(t4);
        
        points.push_back(p3);
        normals.push_back(n_right);
        texture.push_back(t2);
        
        points.push_back(p7);
        normals.push_back(n_right);
        texture.push_back(t3);
        
        points.push_back(p6);
        normals.push_back(n_right);
        texture.push_back(t4);

        // Back
        points.push_back(p3);
        normals.push_back(n_back);
        texture.push_back(t1);

        points.push_back(p4);
        normals.push_back(n_back);
        texture.push_back(t2);

        points.push_back(p7);
        normals.push_back(n_back);
        texture.push_back(t4);

        points.push_back(p4);
        normals.push_back(n_back);
        texture.push_back(t2);

        points.push_back(p8);
        normals.push_back(n_back);
        texture.push_back(t3);

        points.push_back(p7);
        normals.push_back(n_back);
        texture.push_back(t4);

        // Left
        points.push_back(p4);
        normals.push_back(n_left);
        texture.push_back(t1);

        points.push_back(p1);
        normals.push_back(n_left);
        texture.push_back(t2);

        points.push_back(p8);
        normals.push_back(n_left);
        texture.push_back(t4);

        points.push_back(p1);
        normals.push_back(n_left);
        texture.push_back(t2);

        points.push_back(p5);
        normals.push_back(n_left);
        texture.push_back(t3);

        points.push_back(p8);
        normals.push_back(n_left);
        texture.push_back(t4);
    }
    // x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty; for each triangle
    for (int i = 0; i < points.size(); i++){
        return_points.push_back(Point3(points[i], normals[i], texture[i]));
    }
    
    return return_points;
}