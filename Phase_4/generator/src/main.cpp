/*

	Author: Miguel Gomes, Rita Lino, Filipa Gomes, Pedro Pacheco
 Date: 2023-02-03 (YYYY-MM-DD)
 Description: Main file for the generator program
 License: MIT
 Version: 1.0.4
 Changelog:
     1.0.0: Plane generation implemented
     1.0.1: Box generation implemented
     1.0.2: Cone,Cylinder,Pyramid,Sphere generation implemented
     1.0.3: Torus generation implemented
     1.0.4: Generator completed Phase 1
     2.0.0: Beziers Patches implementation started
	 2.0.1: Beziers Patches implementation completed

 Generator <Model> <Model_Info> <Filename> <Extras> -> File

File format:
	number of points
	x,y,z;x,y,z;x,y,z; -> triangle1
	x,y,z;x,y,z;x,y,z; -> triangle2
	x,y,z;x,y,z;x,y,z; -> triangle3
	...
*/



// Standard includes
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>


// Local includes
#include "points.h"
#include "models.h"


using namespace std;


// Global variables

// Help menu
static auto const helpMenu =
"Utilization:\n"
"\tGenerate a box: box [size] [divisions] [filename]\n" //comprimento dos lados da caixa e nome do ficheiro
"\tGenerate a cone: cone [radius] [height] [slices] [stacks] [filename]\n" //raio, altura, numero de fatias e numero de camadas e nome do ficheiro
"\tGenerate a cylinder: cylinder [radius] [height] [slices] [stacks] [filename]\n" //raio, altura, numero de fatias e numero de camadas e nome do ficheiro
"\tGenerate a plane: plane [units] [splits] [filename] [normal_axis:{x,y,z}] [mip}]\n" //comprimento do lado do plano, quantos sub_quadrados no plano e nome do ficheiro para guardar, Extras: eixo normal ao plano, mipmaps?
"\tGenerate a pyramid: pyramid [base] [height] [stacks] [filename]\n" //comprimento da base, altura e numero de camadas e nome do ficheiro
"\tGenerate a sphere: sphere [radius] [slices] [stacks] [filename]\n" //raio, numero de fatias e numero de camadas e nome do ficheiro
"\tGenerate a torus: torus [inner_radius] [outer_radius] [slices] [stacks] [filename]\n" //raio interno, raio externo, numero de fatias e numero de camadas e nome do ficheiro
"\tGenerate a model from a Bezier patch: patch [tesselation] [patch_file] [filename]\n"; //numero de divisoes, nome do ficheiro com os pontos de controlo, nome do ficheiro para guardar


// receives a vector of points and returns a string with the points in the format x,y,z;x,y,z;x,y,z;
string triangle_to_string(vector<Point3> triangle) {
	stringstream ss;
	for (auto point : triangle) {
		auto pos = point.p;
		auto nor = point.n;
		auto tex = point.t;
		ss << pos.x << "," << pos.y << "," << pos.z << ":" << nor.x << "," << nor.y << "," << nor.z << ":" << tex[0] << "," << tex[1] << ";";
	}
	return ss.str();
}


// receives a filename and a vector of points and writes the points to the file
void write_to_file(string filename, vector<Point3> points) {
    ofstream file;
    file.open(filename);
    file << points.size() << endl;
    for (int i = 0; i < points.size(); i+=3) {
		vector<Point3> triangle = {points[i], points[i + 1], points[i + 2]};
		file << triangle_to_string(triangle) << endl;
    }
    file.close();
}



int main(int argc, char *argv[]) {

	// check if there are enough arguments to run the program
	// Minimum arguments: 5 for the plane, 6 for the box, 7 for the sphere and 8 for the cone
	if (argc < 5) {
		cout << helpMenu;
		return 0;
	}

	bool generate = true; // Flag to generate the model

	string model = argv[1]; // Model to generate
	string filename; // Filename to save to
	vector<Point3> points; // Vector of points to save to file

	if (model == "plane") {
		//plane

		// check if there are enough arguments to run the program for the plane
		if (argc < 5) {
			cout << helpMenu;
			generate = false;
		}
		else {
			// get required arguments
			auto units = stod(argv[2]); // Plane length in a single axis
			auto splits = stod(argv[3]); // Number of splits in a single axis
			filename = string(argv[4]); // Filename to save to
			bool mipmaps = false; // Generate with mipmaps
			string _axis = "y"; // Axis to generate the plane perpendicular to
			if (argc > 5) {
				for(int arg = 5; arg < argc; arg++){
					if(string(argv[arg]) == "mip"){
						mipmaps = true;
					}
					else if(string(argv[arg]) == "x"){
						_axis = "x";
					}
					else if(string(argv[arg]) == "z"){
						_axis = "z";
					}
					else{
						cout << helpMenu;
						generate = false;
					}
				}
			}
			auto axis = (char)tolower(_axis[0]); 


			// show generation info
			cout << "Generating plane with " << units << " units in size, " << splits << " splits per axis, perpendicular to the {" << axis << "} axis" << " and saving to " << filename << endl;

			// generate points
			points = draw_plane(units, splits, axis, mipmaps);
		}

	}
	else if (model == "box") {
		//box
		if (argc < 5) {
			cout << helpMenu;
			generate = false;
		}
		else {
			// get required arguments
			auto length = stod(argv[2]); // Box length in the x axis
			auto divisions = stoi(argv[3]); // Number of divisions in the x axis
			filename = string(argv[4]); // Filename to save to

			// show generation info
			cout << "Generating box with length of" << length << " units in the x axis, " << length << " units in the y axis, " << length << " units in the z axis and saving to " << filename << endl;

			// generate points
			points = draw_box(length,divisions);

		}
	}
	else if (model == "sphere") {
		//sphere
		if (argc < 6) {
			cout << helpMenu;
			generate = false;
		}
		else {
			// get required arguments
			auto radius = stod(argv[2]); // Sphere radius
			auto slices = stoi(argv[3]); // Number of slices
			auto stacks = stoi(argv[4]); // Number of stacks
			filename = string(argv[5]); // Filename to save to

			// show generation info
			cout << "Generating sphere with " << radius << " radius, " << slices << " slices and " << stacks << " stacks and saving to " << filename << endl;

			// generate points
			points = draw_sphere(radius, slices, stacks);
		}
	}
	else if (model == "cone") {
		//cone
		if (argc < 7) {
			//cout << helpMenu;
			generate = false;
		}
		else {
			// get required arguments
			auto radius = stod(argv[2]); // Cone radius
			auto height = stod(argv[3]); // Cone height
			auto slices = stoi(argv[4]); // Number of slices
			auto stacks = stoi(argv[5]); // Number of stacks
			filename = string(argv[6]); // Filename to save to

			// show generation info
			cout << "Generating cone with " << radius << " radius, " << height << " height, " << slices << " slices and " << stacks << " stacks and saving to " << filename << endl;

			// generate points
			points = draw_cone(radius, height, slices, stacks);
		}
	}
	else if (model == "cylinder") {
		//cylinder
		if (argc < 7) {
			cout << helpMenu;
			generate = false;
		}
		else {
			// get required arguments
			auto radius = stod(argv[2]); // Cylinder radius
			auto height = stod(argv[3]); // Cylinder height
			auto slices = stoi(argv[4]); // Number of slices
			auto stacks = stoi(argv[5]); // Number of stacks
			filename = string(argv[6]); // Filename to save to

			// show generation info
			cout << "Generating cylinder with " << radius << " radius, " << height << " height, " << slices << " slices and " << stacks << " stacks and saving to " << filename << endl;

			// generate points
			points = draw_cylinder(radius, height, slices, stacks);
		}
	}
	else if (model == "torus") {
		//torus
		if (argc < 7) {
			cout << helpMenu;
			generate = false;
		}
		else {

			// get required arguments
			auto inner_radius = stod(argv[2]); // Torus inner radius
			auto outer_radius = stod(argv[3]); // Torus outer radius
			auto slices = stoi(argv[4]); // Number of slices
			auto stacks = stoi(argv[5]); // Number of stacks
			filename = string(argv[6]); // Filename to save to

			// show generation info
			cout << "Generating torus with " << inner_radius << " inner radius, " << outer_radius << " outer radius, " << slices << " slices and " << stacks << " stacks and saving to " << filename << endl;

			// generate points
			points = draw_torus(inner_radius, outer_radius, slices, stacks);

		}
	}
	else if (model == "pyramid") {
		//pyramid
		if (argc < 6) {
			cout << helpMenu;
			generate = false;
		}
		else {
			// get required arguments
			auto base = stod(argv[2]); // Pyramid base
			auto height = stod(argv[3]); // Pyramid height
			auto stacks = stoi(argv[4]); // Number of stacks
			filename = string(argv[5]); // Filename to save to

			// show generation info
			cout << "Generating pyramid with " << base << " units in base, " << height << " units in height and " << stacks << " stacks and saving to " << filename << endl;

			// generate points
			points = draw_pyramid(base, height, stacks);

		}
	}
	else if (model == "patch") {
		//patch
		if (argc < 5) {
			cout << helpMenu;
			generate = false;
		}
		else {
			// get required arguments
			auto tesselation = stod(argv[2]); // Tesselation level
			auto patch = string(argv[3]); // Patch to draw
			filename = string(argv[4]); // Filename to save to

			// show generation info
			cout << "Generating patch with " << tesselation << " tesselation level, " << patch << " patch and saving to " << filename << endl;

			// generate points
			points = draw_patch(tesselation, patch);

		}
	}
	else {
		cout << helpMenu;
		generate = false;
	}

	if (generate) {
		// save points to file
		write_to_file(filename, points);

		// inform user of success
		cout << "Generated " << points.size() << " points" << endl;
	}

	return 0;
}
