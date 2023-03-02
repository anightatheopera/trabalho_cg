#include <vector>

#include "points.h"


std::vector<Point> draw_plane(double units, double splits, char axis){
	std::vector<Point> points;

	float edge = units / splits;
	float starting_point = -(splits/2) * edge;

	switch (axis) {
		case 'x':
			for (int i = 0; i < splits; i++) {
				for (int j = 0; j < splits; j++) {
					auto common_side_1 = Point(0, starting_point + (i * edge), starting_point + (j * edge));
					auto common_side_2 = Point(0, starting_point + ((i + 1) * edge), starting_point + ((j + 1) * edge));
					auto first_side = Point(0, starting_point + ((i + 1) * edge), starting_point + (j * edge));
					auto second_side = Point(0, starting_point + (i * edge), starting_point + ((j + 1) * edge));
					points.push_back(common_side_1);
					points.push_back(first_side);
					points.push_back(common_side_2);
					points.push_back(common_side_1);
					points.push_back(common_side_2);
					points.push_back(second_side);
				}
			}
			break;
		case 'z':
			for (int i = 0; i < splits; i++) {
				for (int j = 0; j < splits; j++) {
					auto common_side_1 = Point(starting_point + (i * edge), starting_point + (j * edge), 0);
					auto common_side_2 = Point(starting_point + ((i + 1) * edge), starting_point + ((j + 1) * edge), 0);
					auto first_side = Point(starting_point + ((i + 1) * edge), starting_point + (j * edge), 0);
					auto second_side = Point(starting_point + (i * edge), starting_point + ((j + 1) * edge), 0);
					points.push_back(common_side_1);
					points.push_back(first_side);
					points.push_back(common_side_2);
					points.push_back(common_side_1);
					points.push_back(common_side_2);
					points.push_back(second_side);
				}
			}
			break;
		default:
			for (int i = 0; i < splits; i++) {
				for (int j = 0; j < splits; j++) {
					auto common_side_1 = Point(starting_point + (i * edge), 0, starting_point + (j * edge));
					auto common_side_2 = Point(starting_point + ((i + 1) * edge), 0, starting_point + ((j + 1) * edge));
					auto first_side = Point(starting_point + ((i + 1) * edge), 0, starting_point + (j * edge));
					auto second_side = Point(starting_point + (i * edge), 0, starting_point + ((j + 1) * edge));
					points.push_back(common_side_1);
					points.push_back(first_side);
					points.push_back(common_side_2);
					points.push_back(common_side_1);
					points.push_back(common_side_2);
					points.push_back(second_side);
				}
			}
			break;
		}
		return points;
}
