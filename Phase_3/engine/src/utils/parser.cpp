#include "parser.h"

#include <iostream>

#include "tinyxml2.h"
#include "group.h"
#include "model.h"
#include "transformation.h"
#include "camera.h"
#include "colorf.h"
#include "points.h"
#include "scene.h"

using namespace tinyxml2;
using namespace std;

Parser::Parser(string file){
    this->file = file;
}


auto Parser::parse_transformations(XMLElement* element_transform) -> vector<Transformation>{
    vector<Transformation> transformations;
    TransformationType type;
    float x, y, z;
    int angle;
    XMLElement* child_element = element_transform->FirstChildElement();
    while (child_element != nullptr){
        if (strcmp(child_element->Name(), "translate") == 0){
            type = TransformationType::Translate;
            x = atof(child_element->Attribute("x"));
            y = atof(child_element->Attribute("y"));
            z = atof(child_element->Attribute("z"));
        }
        else if (strcmp(child_element->Name(), "rotate") == 0){
            type = TransformationType::Rotate;
            angle = atoi(child_element->Attribute("angle"));
            x = atof(child_element->Attribute("x"));
            y = atof(child_element->Attribute("y"));
            z = atof(child_element->Attribute("z"));
        }
        else if (strcmp(child_element->Name(), "scale") == 0){
            type = TransformationType::Scale;
            x = atof(child_element->Attribute("x"));
            y = atof(child_element->Attribute("y"));
            z = atof(child_element->Attribute("z"));
        }
        transformations.push_back(Transformation(type, x, y, z, angle));
        child_element = child_element->NextSiblingElement();
    }
    return transformations;
}

auto Parser::parse_models(XMLElement* models_element) -> vector<Model>{
    vector<Model> models;
    XMLElement* model_element = models_element->FirstChildElement();
    while (model_element != nullptr){
	Color color = Color();
        string file = model_element->Attribute("file");
	auto color_element = model_element->FirstChildElement("color");
	if (color_element != nullptr){
		float r = (float) atoi(color_element->Attribute("r")) / 255;
		float g = (float) atoi(color_element->Attribute("g")) / 255;
		float b = (float) atoi(color_element->Attribute("b")) / 255;
		color = Color(r, g, b);
	}
	else{
		string color_name = model_element->Attribute("color") ? model_element->Attribute("color") : "#FFFFFF";
		color = Color(color_name);
	}
	models.push_back(Model(file, color));
        model_element = model_element->NextSiblingElement();
    }
    return models;
}


auto Parser::parse_camera(XMLElement* camera_element, int screen_width, int screen_height) -> Camera {
    // Default values
    Point position(5.0, 3.0, 5.0);
    Point lookAt(0.0, 0.0, 0.0);
    Point up(0.0, 1.0, 0.0);
    Point perspective(60.0, 1.0, 1000.0);

    if (!camera_element) {
        return Camera();
    }

    const XMLElement* child_camera = camera_element->FirstChildElement("position");
    if (child_camera) {
        const double x = std::stod(child_camera->Attribute("x"));
        const double y = std::stod(child_camera->Attribute("y"));
        const double z = std::stod(child_camera->Attribute("z"));
        position = Point(x, y, z);
    }

    child_camera = child_camera->NextSiblingElement("lookAt");
    if (child_camera) {
        const double x = std::stod(child_camera->Attribute("x"));
        const double y = std::stod(child_camera->Attribute("y"));
        const double z = std::stod(child_camera->Attribute("z"));
        lookAt = Point(x, y, z);
    }

    child_camera = child_camera->NextSiblingElement("up");
    if (child_camera) {
        const double x = std::stod(child_camera->Attribute("x"));
        const double y = std::stod(child_camera->Attribute("y"));
        const double z = std::stod(child_camera->Attribute("z"));
        up = Point(x, y, z);
    }

    child_camera = child_camera->NextSiblingElement("projection");
    if (child_camera) {
        const double fov = std::stod(child_camera->Attribute("fov"));
        const double near = std::stod(child_camera->Attribute("near"));
        const double far = std::stod(child_camera->Attribute("far"));
        perspective = Point(fov, near, far);
    }

    return Camera(position, lookAt, up, perspective, screen_width, screen_height);
}

auto Parser::parse_group(XMLElement* element_group) -> Group {
    Group group;
    XMLElement* child_element = element_group->FirstChildElement();
    string name = element_group->Attribute("name");
    group.set_name(name);
    while (child_element != nullptr){
        if (strcmp(child_element->Name(), "group") == 0){
            group.addSubgroup(parse_group(child_element));
        }
        else if (strcmp(child_element->Name(), "models") == 0){
            group.models = parse_models(child_element);
        }
        else if (strcmp(child_element->Name(), "transform") == 0){
            group.transformations = parse_transformations(child_element);
        }
        child_element = child_element->NextSiblingElement();
    }
    return group;
}


auto Parser::parse() -> Scene {
    XMLDocument doc;

    XMLError eResult = doc.LoadFile(this->file.c_str());
	if (eResult != XML_SUCCESS) throw runtime_error("Error loading file");
    
    XMLNode* root = doc.FirstChildElement("world");

    auto window = root->FirstChildElement("window");
	auto screen_width = stoi(window->Attribute("width"));
	auto screen_height = stoi(window->Attribute("height"));

    XMLElement* child_element = root->FirstChildElement();
    Scene scene;

    while (child_element != nullptr){
        if (strcmp(child_element->Name(), "group") == 0){
            scene.group = parse_group(child_element);
        }
        else if (strcmp(child_element->Name(), "camera") == 0){
            scene.camera = parse_camera(child_element, screen_width, screen_height);
        }
        child_element = child_element->NextSiblingElement();
    }
    return scene;
}
