#include <vector>
#include <cmath>
#define USE_MATH_DEFINES

#include "points.h"

std::vector<Point3> draw_cylinder(double radius, double height, int slices, int stacks){
    std::vector<Point3> return_points;
    std::vector<Point> points;
    std::vector<Point> normal;
    std::vector<Point> texture;
    auto staring_point = -height/2;
    auto step = height/stacks;
    auto center_bottom = Point(0,staring_point,0);
    auto center_top = Point(0,staring_point+height,0);

    auto texture_stack_step = (1.0f-0.375f)/stacks;
    auto texture_stack_starting_point = 0.375;
    auto texture_slice_step = 1.0f/slices;

    for (int i = 0; i < slices; i++) {
		float alpha = ((2*M_PI)/slices)*i;
		float beta = ((2*M_PI)/slices)*(i+1);

        for (int j=0; j < stacks; j++){

            auto p1 = Point(radius*sin(alpha),staring_point+(step*j),radius*cos(alpha));
            auto p2 = Point(radius*sin(beta),staring_point+(step*j),radius*cos(beta));
            auto p3 = Point(radius*sin(beta),staring_point+(step*(j+1)),radius*cos(beta));
            auto p4 = Point(radius*sin(alpha),staring_point+(step*(j+1)),radius*cos(alpha));

            auto t1 = Point(texture_slice_step*i,texture_stack_starting_point+texture_stack_step*j,0);
            auto t2 = Point(texture_slice_step*i+1,texture_stack_starting_point+texture_stack_step*j,0);
            auto t3 = Point(texture_slice_step*i+1,texture_stack_starting_point+texture_stack_step*j+1,0);
            auto t4 = Point(texture_slice_step*i,texture_stack_starting_point+texture_stack_step*j+1,0);

            if (j == stacks-1){
                points.push_back(p4);
                normal.push_back(Point(0,1,0));
                texture.push_back(Point(0.4375f + 0.1875 * sin(alpha),0.1875f + 0.1875 * cos(alpha),0));

                points.push_back(p3);
                normal.push_back(Point(0,1,0));
                texture.push_back(Point(0.4375f + 0.1875 * sin(beta),0.1875f + 0.1875 * cos(beta),0));

                points.push_back(center_top);
                normal.push_back(Point(0,1,0));
                texture.push_back(Point(0.4375f,0.1875f,0));
            }

            if (j == 0){
                points.push_back(center_bottom);
                normal.push_back(Point(0,-1,0));
                texture.push_back(Point(0.8125f,0.1875f,0));
                points.push_back(p2);
                normal.push_back(Point(0,-1,0));
                texture.push_back(Point(0.8125f + 0.1875 * sin(beta),0.1875f + 0.1875 * cos(beta),0));
                points.push_back(p1);
                normal.push_back(Point(0,-1,0));
                texture.push_back(Point(0.8125f + 0.1875 * sin(alpha),0.1875f + 0.1875 * cos(alpha),0));
            }

            auto n1 = Point(sin(alpha),0,cos(alpha));
            auto n2 = Point(sin(beta),0,cos(beta));
            n1.normalize();
            n2.normalize();

            points.push_back(p1);
            normal.push_back(n1);
            texture.push_back(t1);
            points.push_back(p2);
            normal.push_back(n2);
            texture.push_back(t2);
            points.push_back(p3);
            normal.push_back(n2);
            texture.push_back(t3);
            points.push_back(p1);
            normal.push_back(n1);
            texture.push_back(t1);
            points.push_back(p3);
            normal.push_back(n2);
            texture.push_back(t3);
            points.push_back(p4);
            normal.push_back(n1);
            texture.push_back(t4);
        }
	}


    // x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty; for each triangle
    for (int i = 0; i < points.size(); i++){
        return_points.push_back(Point3(points[i], normal[i], texture[i]));
    }
    
    return return_points;
}