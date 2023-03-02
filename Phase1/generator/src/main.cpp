#include<iostream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

static auto const helpMenu =
"Utilization:\n"
"\tGenerate a plane: plane [units] [splits] [filename] [normal_axis]\n" //eixo do plano, comprimento do lado do plano, quantos sub_quadrados no plano e nome do ficheiro para guardar
"\tGenerate a box: box [side_X] [side_Y] [side_Z] [filename]\n" //comprimento dos lados da caixa e nome do ficheiro
"\tGenerate a sphere: sphere [radius] [slices] [stacks] [filename]\n" //raio, numero de fatias e numero de camadas e nome do ficheiro
"\tGenerate a cone: cone [radius] [height] [slices] [stacks] [filename]\n"; //raio, altura, numero de fatias e numero de camadas e nome do ficheiro

int main(int argc, char *argv[]) {
	if (argc < 4) {
		std::cout << helpMenu;
		return 0;
	}
	auto todo = std::string(argv[1]);

	if (todo == "plane") {
		//plane
		auto units = std::stof(argv[2]);
		auto splits = std::stod(argv[3]);
		auto filename = std::string(argv[4]);
		auto axis = argc > 5 ? std::string(argv[5]) : "y";
		std::vector<std::string> vertices;
		if (axis == "y") {
			for (int i = 0; i <= splits; i++) {
				for (int j = 0; j <= splits; j++) {
					std::stringstream ss;
					ss << i * units << ",0 ," << j * units << "\n";
					vertices.push_back(ss.str());
				}
			}
		}
		else if (axis == "x") {
			for (int i = 0; i <= splits; i++) {
				for (int j = 0; j <= splits; j++) {
					std::stringstream ss;
					ss << "0, " << i * units << ", " << j * units << "\n";
					vertices.push_back(ss.str());
				}
			}

		}
		else if (axis == "z") {
			for (int i = 0; i <= splits; i++) {
				for (int j = 0; j <= splits; j++) {
					std::stringstream ss;
					ss << i * units << ", " << j * units << ", 0\n";
					vertices.push_back(ss.str());
				}
			}

		}
		else {
			std::cout << "Invalid side\n";
			return 0;
		}

		    std::stringstream ss;
		    for (auto it = vertices.begin(); it != vertices.end(); it++)    {
			    if (it != vertices.begin()) {}
			    ss << *it;
		    }
 
		std::cout << "Generating plane...\n" << ss.str() << std::endl;

	}
	else if (todo == "box") {
		//box
		std::cout << "box" << std::endl;
	}
	else if (todo == "sphere") {
		//sphere
		std::cout << "sphere" << std::endl;
	}
	else if (todo == "cone") {
		//cone
		std::cout << "cone" << std::endl;
	}
	else {
		std::cout << helpMenu;
	}
	return 0;
}
