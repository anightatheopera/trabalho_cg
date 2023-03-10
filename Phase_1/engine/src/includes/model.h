#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include "points.h"

class Model {

    public:
	std::string file;
	std::vector<Point> points;
        //Color;
        //Texture;
        //Material;
        //Transformations;
        //Animation;
        //Light;

        Model(std::string file, std::vector<Point> points);

};

#endif
