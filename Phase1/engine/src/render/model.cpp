#include <vector>
#include <string>

#include "points.h"
#include "model.h"


Model::Model( std::string file, std::vector<Point> points){
    this->file = file;
    this->points = points;
}
