#include <vector>
#include <iostream>
#include <ostream>

#include "points.h"


std::vector<Point> draw_square(Point x1, Point x2, Point x3, Point x4){
    std::vector<Point> points;
    points.push_back(x1);
    points.push_back(x2);
    points.push_back(x3);
    points.push_back(x3);
    points.push_back(x2);
    points.push_back(x4);
    return points;
}

std::vector<Point3> draw_box(double length, int divisions){
    std::vector<Point3> return_points;
    std::vector<Point> points;
    std::vector<Point> normal;
    std::vector<Point> texture;
    auto half_len = length / 2;
    auto edge = length / divisions;

    // face da frente e trás
    for (int i = 0; i < divisions; i++){
        for (int j = 0; j < divisions; j++){
            auto x_c = i;
            auto y_c = j;
            auto x_n = i + 1;
            auto y_n = j + 1;

            auto t1 = Point((float)x_c/divisions, (float)y_c/divisions, 0);
            auto t2 = Point((float)x_n/divisions, (float)y_c/divisions, 0);
            auto t3 = Point((float)x_c/divisions, (float)y_n/divisions, 0);
            auto t4 = Point((float)x_n/divisions, (float)y_n/divisions, 0);

            auto face = draw_square(Point(edge*j,edge*i,0), 
                                    Point(edge*(j + 1),edge*i,0), 
                                    Point(edge*j,edge*(i + 1),0), 
                                    Point(edge*(j + 1),edge*(i + 1),0)
                                    );
            for(auto p : face){
                p.substract(Point(half_len, half_len, -half_len));
                points.push_back(p);
                normal.push_back(Point(0,0,-1));
            }
            texture.push_back(t1);
            texture.push_back(t2);
            texture.push_back(t3);
            texture.push_back(t3);
            texture.push_back(t2);
            texture.push_back(t4);
            auto face2 = draw_square(Point(edge*j,edge*i,0), 
                                    Point(edge*j,edge*(i + 1),0), 
                                    Point(edge*(j + 1),edge*i,0), 
                                    Point(edge*(j + 1),edge*(i + 1),0)
                                    );
            for(auto p : face2){
                p.substract(Point(half_len, half_len, half_len));
                points.push_back(p);
                normal.push_back(Point(0,0,1));
            }  
            texture.push_back(t1);
            texture.push_back(t4);
            texture.push_back(t2);
            texture.push_back(t2);
            texture.push_back(t4);
            texture.push_back(t3);
        }
    }

    // face de cima e baixo
    for (int i = 0; i < divisions; i++){
        for (int j = 0; j < divisions; j++){

            auto x_c = i;
            auto y_c = j;
            auto x_n = i + 1;
            auto y_n = j + 1;

            auto t1 = Point((float)x_c/divisions, (float)y_c/divisions, 0);
            auto t2 = Point((float)x_n/divisions, (float)y_c/divisions, 0);
            auto t3 = Point((float)x_c/divisions, (float)y_n/divisions, 0);
            auto t4 = Point((float)x_n/divisions, (float)y_n/divisions, 0);

            auto face = draw_square(Point(edge*j,0,edge*i), 
                                    Point(edge*(j + 1),0,edge*i), 
                                    Point(edge*j,0,edge*(i + 1)), 
                                    Point(edge*(j + 1),0,edge*(i + 1))
                                    );
            for(auto p : face){
                p.substract(Point(half_len, half_len, half_len));
                points.push_back(p);
                normal.push_back(Point(0,1,0));
            }
            texture.push_back(t1);
            texture.push_back(t2);
            texture.push_back(t4);
            texture.push_back(t4);
            texture.push_back(t2);
            texture.push_back(t3);

            auto face2 = draw_square(Point(edge*j,0,edge*i), 
                                    Point(edge*j,0,edge*(i + 1)), 
                                    Point(edge*(j + 1),0,edge*i), 
                                    Point(edge*(j + 1),0,edge*(i + 1))
                                    );
            for(auto p : face2){
                p.substract(Point(half_len, -half_len, half_len));
                points.push_back(p);
                normal.push_back(Point(0,-1,0));
            }  
            texture.push_back(t1);
            texture.push_back(t4);
            texture.push_back(t2);
            texture.push_back(t2);
            texture.push_back(t4);
            texture.push_back(t3);
        }
    }

    // face da direita e esquerda
    for (int i = 0; i < divisions; i++){
        for (int j = 0; j < divisions; j++){
            auto x_c = i;
            auto y_c = j;
            auto x_n = i + 1;
            auto y_n = j + 1;

            auto t1 = Point((float)x_c/divisions, (float)y_c/divisions, 0);
            auto t2 = Point((float)x_n/divisions, (float)y_c/divisions, 0);
            auto t3 = Point((float)x_c/divisions, (float)y_n/divisions, 0);
            auto t4 = Point((float)x_n/divisions, (float)y_n/divisions, 0);

            auto face = draw_square(Point(0,edge*j,edge*i), 
                                    Point(0,edge*(j + 1),edge*i), 
                                    Point(0,edge*j,edge*(i + 1)), 
                                    Point(0,edge*(j + 1),edge*(i + 1))
                                    );
            for(auto p : face){
                p.substract(Point(-half_len, half_len, half_len));
                points.push_back(p);
                normal.push_back(Point(1,0,0));
            }
            texture.push_back(t1);
            texture.push_back(t2);
            texture.push_back(t4);
            texture.push_back(t4);
            texture.push_back(t2);
            texture.push_back(t3);
            auto face2 = draw_square(Point(0,edge*j,edge*i), 
                                    Point(0,edge*j,edge*(i + 1)), 
                                    Point(0,edge*(j + 1),edge*i), 
                                    Point(0,edge*(j + 1),edge*(i + 1))
                                    );
            for(auto p : face2){
                p.substract(Point(half_len, half_len, half_len));
                points.push_back(p);
                normal.push_back(Point(-1,0,0));
            }  
            texture.push_back(t1);
            texture.push_back(t4);
            texture.push_back(t2);
            texture.push_back(t2);
            texture.push_back(t4);
            texture.push_back(t3);
        }
    }

    // x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty;x,y,z:nx,ny,nz:tx,ty; for each triangle
    for (int i = 0; i < points.size(); i++){
        return_points.push_back(Point3(points[i], normal[i], texture[i]));
    }
    
    return return_points;
}