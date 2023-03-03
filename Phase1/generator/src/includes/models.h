#include <vector>
#include "points.h"

std::vector<Point> draw_box(double side_x, double side_y, double side_z); //box
std::vector<Point> draw_cone(double radius, double height, int slices, int stacks); //cone
std::vector<Point> draw_cylinder(double radius, double height, int slices, int stacks); //cylinder
std::vector<Point> draw_plane(double units, double splits, char axis); //plano
std::vector<Point> draw_pyramid(double base, double height, int stacks); //pyramid
std::vector<Point> draw_sphere(double radius, int slices, int stacks); //sphere
std::vector<Point> draw_torus(double inner_radius, double outer_radius, int slices, int stacks); //torus
