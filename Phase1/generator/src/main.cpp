#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

#include "points.h"
#include "models.h"

using namespace std;

static auto const helpMenu =
"Utilization:\n"
"\tGenerate a plane: plane [units] [splits] [filename] [normal_axis:{x,y,z}] [colors:{RED,GREEN,BLUE}]\n" //comprimento do lado do plano, quantos sub_quadrados no plano e nome do ficheiro para guardar, Extras: eixo normal do plano, cores?
"\tGenerate a box: box [side_X] [side_Y] [side_Z] [filename]\n" //comprimento dos lados da caixa e nome do ficheiro
"\tGenerate a sphere: sphere [radius] [slices] [stacks] [filename]\n" //raio, numero de fatias e numero de camadas e nome do ficheiro
"\tGenerate a cone: cone [radius] [height] [slices] [stacks] [filename]\n"; //raio, altura, numero de fatias e numero de camadas e nome do ficheiro

void write_to_file(string filename, vector<Point> points) {
    ofstream file;
    file.open(filename);
    file << points.size() << endl;
    for (auto point : points) {
	file << point.getX() << "," << point.getY() << "," << point.getZ() << endl;
    }
    file.close();
}


int main(int argc, char *argv[]) {
	if (argc < 4) {
		cout << helpMenu;
		return 0;
	}
	auto todo = string(argv[1]);

	if (todo == "plane") {
		//plane
		auto units = stod(argv[2]);
		auto splits = stod(argv[3]);
		auto filename = string(argv[4]);
		auto _axis = argc > 5 ? string(argv[5]) : "y";
		auto axis = (char)tolower(_axis[0]);

		cout << "Generating plane with " << units << " units in size, " << splits << " splits per axis, perpendicular to the" << axis << " axis" << " and saving to " << filename << endl;

		auto points = draw_plane(units, splits, axis);
		cout << "Generated " << points.size() << " points" << endl;

		write_to_file(filename, points);
	}
	else if (todo == "box") {
		//box
		cout << "box" << endl;
	}
	else if (todo == "sphere") {
		//sphere
		cout << "sphere" << endl;
	}
	else if (todo == "cone") {
		//cone
		cout << "cone" << endl;
	}
	else {
		cout << helpMenu;
	}
	return 0;
}
