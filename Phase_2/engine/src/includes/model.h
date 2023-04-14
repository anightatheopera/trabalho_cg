#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <fstream>
#include <string>
#include <sstream>

#include "points.h"
#include "colorf.h"

class Model {

    public:
	    std::string file;
	    std::vector<Point> points;
	    std::string texture;
	    Color color;

        //Texture;
        //Material;
        //Transformations;
        //Animation;
        //Light;

        Model(std::string file, std::vector<Point> points,std::string texture, Color color);
        Model(std::string file);
	Model(std::string file, Color color);
	Model();

        auto show() -> void;

        auto load_file() -> void;
        auto render() -> void;

};

#endif
