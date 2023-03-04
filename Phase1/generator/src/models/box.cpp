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

std::vector<Point> draw_box(double length, int divisions){
    std::vector<Point> points;
    auto half_len = length / 2;
    auto edge = length / divisions;

    // face da frente e trás
    for (int i = 0; i < divisions; i++){
        for (int j = 0; j < divisions; j++){
            auto face = draw_square(Point(edge*j,edge*i,0), 
                                    Point(edge*(j + 1),edge*i,0), 
                                    Point(edge*j,edge*(i + 1),0), 
                                    Point(edge*(j + 1),edge*(i + 1),0)
                                    );
            for(auto p : face){
                p.substract(Point(half_len, half_len, -half_len));
                points.push_back(p);
            }
            auto face2 = draw_square(Point(edge*j,edge*i,0), 
                                    Point(edge*j,edge*(i + 1),0), 
                                    Point(edge*(j + 1),edge*i,0), 
                                    Point(edge*(j + 1),edge*(i + 1),0)
                                    );
            for(auto p : face2){
                p.substract(Point(half_len, half_len, half_len));
                points.push_back(p);
            }  
        }
    }

    // face de cima e baixo
    for (int i = 0; i < divisions; i++){
        for (int j = 0; j < divisions; j++){
            auto face = draw_square(Point(edge*j,0,edge*i), 
                                    Point(edge*(j + 1),0,edge*i), 
                                    Point(edge*j,0,edge*(i + 1)), 
                                    Point(edge*(j + 1),0,edge*(i + 1))
                                    );
            for(auto p : face){
                p.substract(Point(half_len, half_len, half_len));
                points.push_back(p);
            }
            auto face2 = draw_square(Point(edge*j,0,edge*i), 
                                    Point(edge*j,0,edge*(i + 1)), 
                                    Point(edge*(j + 1),0,edge*i), 
                                    Point(edge*(j + 1),0,edge*(i + 1))
                                    );
            for(auto p : face2){
                p.substract(Point(half_len, -half_len, half_len));
                points.push_back(p);
            }  
        }
    }

    // face da direita e esquerda
    for (int i = 0; i < divisions; i++){
        for (int j = 0; j < divisions; j++){
            auto face = draw_square(Point(0,edge*j,edge*i), 
                                    Point(0,edge*(j + 1),edge*i), 
                                    Point(0,edge*j,edge*(i + 1)), 
                                    Point(0,edge*(j + 1),edge*(i + 1))
                                    );
            for(auto p : face){
                p.substract(Point(-half_len, half_len, half_len));
                points.push_back(p);
            }
            auto face2 = draw_square(Point(0,edge*j,edge*i), 
                                    Point(0,edge*j,edge*(i + 1)), 
                                    Point(0,edge*(j + 1),edge*i), 
                                    Point(0,edge*(j + 1),edge*(i + 1))
                                    );
            for(auto p : face2){
                p.substract(Point(half_len, half_len, half_len));
                points.push_back(p);
            }  
        }
    }
    
    return points;
}