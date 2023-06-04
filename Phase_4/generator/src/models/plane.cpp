#include <vector>
#include <iostream>
#include <ostream>

#include "points.h"


std::vector<Point3> draw_plane(double units, double splits, char axis, bool mipmaps){
	std::vector<Point3> points;

	std::vector<Point> coords;
	std::vector<Point> normals;
	std::vector<Point> textures;

	float edge = units / splits;
	float starting_point = -(splits/2) * edge;

	switch (axis) {
		case 'x':
			for (int i = 0; i < splits; i++) {
				for (int j = 0; j < splits; j++) {

					auto current_y = i;
					auto current_z = j;
					auto next_y = i+1;
					auto next_z = j+1;

					auto p1 = Point(0, starting_point + (current_y * edge), starting_point + (current_z * edge));
					auto p2 = Point(0, starting_point + (next_y * edge), starting_point + (current_z * edge));
					auto p3 = Point(0, starting_point + (next_y * edge), starting_point + (next_z * edge));
					auto p4 = Point(0, starting_point + (current_y * edge), starting_point + (next_z * edge));

					if (next_y > splits) {
						next_y = 0;
					}
					if (next_z > splits) {
						next_z = 0;
					}

					auto normal = Point(1, 0, 0);

					auto t1 = Point(current_y/splits, current_z/splits,0);
					auto t2 = Point(next_y/splits, current_z/splits,0);
					auto t3 = Point(next_y/splits, next_z/splits,0);
					auto t4 = Point(current_y/splits, next_z/splits,0);

					if (mipmaps){
						t1 = Point(0,0,0);
						t2 = Point(1,0,0);
						t3 = Point(1,1,0);
						t4 = Point(0,1,0);
					}

					coords.push_back(p1);
					coords.push_back(p2);
					coords.push_back(p3);
					coords.push_back(p1);
					coords.push_back(p3);
					coords.push_back(p4);


					textures.push_back(t1);
					textures.push_back(t2);
					textures.push_back(t3);
					textures.push_back(t1);
					textures.push_back(t3);
					textures.push_back(t4);



					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);

				}
			}
			break;
		case 'z':
			for (int i = 0; i < splits; i++) {
				for (int j = 0; j < splits; j++) {

					auto current_x = i;
					auto current_y = j;
					auto next_x = i+1;
					auto next_y = j+1;

					auto p1 = Point(starting_point + (current_x * edge), starting_point + (current_y * edge), 0);
					auto p2 = Point(starting_point + (next_x * edge), starting_point + (current_y * edge), 0);
					auto p3 = Point(starting_point + (next_x * edge), starting_point + (next_y * edge), 0);
					auto p4 = Point(starting_point + (current_x * edge), starting_point + (next_y * edge), 0);

					if (next_x > splits) {
						next_x = 0;
					}
					if (next_y > splits) {
						next_y = 0;
					}

					auto normal = Point(0, 0, 1);

					auto t1 = Point(current_x/splits, current_y/splits,0);
					auto t2 = Point(next_x/splits, current_y/splits,0);
					auto t3 = Point(next_x/splits, next_y/splits,0);
					auto t4 = Point(current_x/splits, next_y/splits,0);

					if (mipmaps){
						t1 = Point(0,0,0);
						t2 = Point(1,0,0);
						t3 = Point(1,1,0);
						t4 = Point(0,1,0);
					}

					coords.push_back(p1);
					coords.push_back(p2);
					coords.push_back(p3);
					coords.push_back(p1);
					coords.push_back(p3);
					coords.push_back(p4);


					textures.push_back(t1);
					textures.push_back(t2);
					textures.push_back(t3);
					textures.push_back(t1);
					textures.push_back(t3);
					textures.push_back(t4);

					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);
				}
			}
			break;
		default:
			for (int i = 0; i < splits; i++) {
				for (int j = 0; j < splits; j++) {

					auto next_i = i+1;
					auto next_j = j+1;

					auto p1 = Point(starting_point + (i * edge), 0, starting_point + (j * edge));
					auto p4 = Point(starting_point + (next_i * edge), 0, starting_point + (j * edge));
					auto p3 = Point(starting_point + (next_i * edge), 0, starting_point + (next_j * edge));
					auto p2 = Point(starting_point + (i * edge), 0, starting_point + (next_j * edge));

					if (next_i > splits) {
						next_i = 0;
					}
					if (next_j > splits) {
						next_j = 0;
					}
					
					auto normal = Point(0, 1, 0);

					auto t1 = Point(i/splits, j/splits,0);
					auto t2 = Point(next_i/splits, j/splits,0);
					auto t3 = Point(next_i/splits, next_j/splits,0);
					auto t4 = Point(i/splits, next_j/splits,0);

					if (mipmaps){
						t1 = Point(0,0,0);
						t2 = Point(1,0,0);
						t3 = Point(1,1,0);
						t4 = Point(0,1,0);
					}

					coords.push_back(p1);
					coords.push_back(p2);
					coords.push_back(p3);
					coords.push_back(p1);
					coords.push_back(p3);
					coords.push_back(p4);


					textures.push_back(t1);
					textures.push_back(t2);
					textures.push_back(t3);
					textures.push_back(t1);
					textures.push_back(t3);
					textures.push_back(t4);

					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);
				}
			}
			break;
		}

		for (int i = 0; i < coords.size(); i++) {
			points.push_back(Point3(coords[i], normals[i], textures[i]));
		}
		return points;
}
