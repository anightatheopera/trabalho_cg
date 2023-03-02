#include <vector>
#include <array>
#include "points.h"

std::vector<Point> draw_plane(double units, double splits, char axis); //plano
std::array<std::vector<Point>,3> drawSphere(double radius, int slices, int stacks); //sphere
std::array<std::vector<Point>,3> drawBox(float length, float width, float height); //box
std::array<std::vector<Point>,3> drawCone(double radius, double height, int slices, int stacks); //cone
std::array<std::vector<Point>,3> drawBoxD(float length, float width, float height, int divisions); //box pt2
std::array<std::vector<Point>,3> drawTorus(double dist, double radius, int slices, int stacks); //torus
std::array<std::vector<Point>,3> drawPatch(std::string file , int tess); //patch

