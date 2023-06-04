// Purpose: Header file for models.cpp
#ifndef MODELS_H
#define MODELS_H
#include <vector>
#include <string>
#include "points.h"

std::vector<Point3> draw_box(double length, int divisions); //box
std::vector<Point3> draw_cone(double radius, double height, int slices, int stacks); //cone
std::vector<Point3> draw_cylinder(double radius, double height, int slices, int stacks); //cylinder
std::vector<Point3> draw_plane(double units, double splits, char axis, bool mipmaps); //plano
std::vector<Point3> draw_pyramid(double base, double height, int stacks); //pyramid
std::vector<Point3> draw_sphere(double radius, int slices, int stacks); //sphere
std::vector<Point3> draw_torus(double inner_radius, double outer_radius, int slices, int stacks); //torus
std::vector<Point3> draw_patch(int tesselation, std::string patch_file); //bezier patch

#endif