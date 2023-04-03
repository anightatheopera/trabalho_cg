#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <fstream>
#include <string>
#include <sstream>

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
        Model(std::string file);

        auto show() -> void;

        auto load_file() -> void;
        auto render() -> void;

};

#endif
