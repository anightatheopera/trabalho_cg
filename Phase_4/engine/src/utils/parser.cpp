#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

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
#include "curve.h"
#include "light.h"

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
    Curve c = Curve();
    while (child_element != nullptr){
        if (strcmp(child_element->Name(), "translate") == 0){
            float time = child_element->Attribute("time") ? atof(child_element->Attribute("time")) : -1;
            if (time > -1){
		    	type = TransformationType::TimedTranslate;
            		string align_s = child_element->Attribute("align") ? child_element->Attribute("align") : "false";
            		bool align = align_s == "true" ? true : false;
		    	XMLElement* points_element = child_element->FirstChildElement();
		    	while (points_element != nullptr){
			    	x = points_element->Attribute("x") ? atof(points_element->Attribute("x")) : 0;
			    	y = points_element->Attribute("y") ? atof(points_element->Attribute("y")) : 0;
			    	z = points_element->Attribute("z") ? atof(points_element->Attribute("z")) : 0;
			    	c.add_control_point(Point(x, y, z));
			    	points_element = points_element->NextSiblingElement();
		    	}
			transformations.push_back(Transformation(type, time, align, c));
	    }
            else{
                type = TransformationType::Translate;
            	x = atof(child_element->Attribute("x")) ? atof(child_element->Attribute("x")) : 0;
            	y = atof(child_element->Attribute("y")) ? atof(child_element->Attribute("y")) : 0;
            	z = atof(child_element->Attribute("z")) ? atof(child_element->Attribute("z")) : 0;
		transformations.push_back(Transformation(type, x, y, z));
	    }
        }
        else if (strcmp(child_element->Name(), "rotate") == 0){
            float time = child_element->Attribute("time") ? atof(child_element->Attribute("time")) : -1;
            if (time > -1){
                type = TransformationType::TimedRotate;
		        x = atof(child_element->Attribute("x")) ? atof(child_element->Attribute("x")) : 0;
            	y = atof(child_element->Attribute("y")) ? atof(child_element->Attribute("y")) : 0;
            	z = atof(child_element->Attribute("z")) ? atof(child_element->Attribute("z")) : 0;
            	transformations.push_back(Transformation(type, x, y, z, time));
	    }
	    else{
                type = TransformationType::Rotate;
		angle = atof(child_element->Attribute("angle")) ? atof(child_element->Attribute("angle")) : 0;
            	x = atof(child_element->Attribute("x")) ? atof(child_element->Attribute("x")) : 0;
            	y = atof(child_element->Attribute("y")) ? atof(child_element->Attribute("y")) : 0;
            	z = atof(child_element->Attribute("z")) ? atof(child_element->Attribute("z")) : 0;
            	transformations.push_back(Transformation(type, x, y, z, angle));
	    }
	}
        else if (strcmp(child_element->Name(), "scale") == 0){
            float time = child_element->Attribute("time") ? atof(child_element->Attribute("time")) : -1;
            if (time > -1)
                type = TransformationType::TimedScale;
            else
                type = TransformationType::Scale;
            x = atof(child_element->Attribute("x")) ? atof(child_element->Attribute("x")) : 0;
            y = atof(child_element->Attribute("y")) ? atof(child_element->Attribute("y")) : 0;
            z = atof(child_element->Attribute("z")) ? atof(child_element->Attribute("z")) : 0;
            transformations.push_back(Transformation(type, x, y, z,time));
        }
        child_element = child_element->NextSiblingElement();
    }
    return transformations;
}

auto Parser::parse_models(XMLElement* models_element) -> vector<Model>{
    vector<Model> models;
    XMLElement* model_element = models_element->FirstChildElement();
    while (model_element != nullptr){
        string texture = model_element->Attribute("texture") ? model_element->Attribute("texture") : "";
        string file = model_element->Attribute("file") ? model_element->Attribute("file") : "ERROR";
        auto texture_element = model_element->FirstChildElement("texture");
        auto reflection = Reflection();
        if (texture_element != nullptr){
            texture = texture_element->Attribute("file") ? texture_element->Attribute("file") : "";
        }
        else{
             reflection = parse_reflections(model_element->FirstChildElement("color"));
        }
        models.push_back(Model(file, texture, reflection));
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
        const double x = std::stof(child_camera->Attribute("x")) ;
        const double y = std::stof(child_camera->Attribute("y"));
        const double z = std::stof(child_camera->Attribute("z"));
        position = Point(x, y, z);
    }

    child_camera = child_camera->NextSiblingElement("lookAt");
    if (child_camera) {
        const double x = std::stof(child_camera->Attribute("x"));
        const double y = std::stof(child_camera->Attribute("y"));
        const double z = std::stof(child_camera->Attribute("z"));
        lookAt = Point(x, y, z);
    }

    child_camera = child_camera->NextSiblingElement("up");
    if (child_camera) {
        const double x = std::stof(child_camera->Attribute("x"));
        const double y = std::stof(child_camera->Attribute("y"));
        const double z = std::stof(child_camera->Attribute("z"));
        up = Point(x, y, z);
    }

    child_camera = child_camera->NextSiblingElement("projection");
    if (child_camera) {
        const double fov = std::stof(child_camera->Attribute("fov"));
        const double near = std::stof(child_camera->Attribute("near"));
        const double far = std::stof(child_camera->Attribute("far"));
        perspective = Point(fov, near, far);
    }

    return Camera(position, lookAt, up, perspective, screen_width, screen_height);
}

auto Parser::parse_group(XMLElement* element_group) -> Group {
    Group group;
    XMLElement* child_element = element_group->FirstChildElement();
    string name = element_group->Attribute("name") ? element_group->Attribute("name") : "";
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

auto Parser::parse_reflections(XMLElement* element_material) -> Reflection {
    Reflection reflection = Reflection();
    if (element_material != nullptr){
        auto diffuse = element_material->FirstChildElement("diffuse");
        if (diffuse != nullptr){
            auto r = diffuse->Attribute("R") ? atof(diffuse->Attribute("R")) : 200;
            auto g = diffuse->Attribute("G") ? atof(diffuse->Attribute("G")) : 200;
            auto b = diffuse->Attribute("B") ? atof(diffuse->Attribute("B")) : 200;
            float rgb[3] = {(float)r/255, (float)g/255, (float)b/255};
            reflection.diffuse = Color(rgb[0], rgb[1], rgb[2]);
        }
        
        auto ambient = element_material->FirstChildElement("ambient");
        if (ambient != nullptr){
            auto r = ambient->Attribute("R") ? atof(ambient->Attribute("R")) : 50;
            auto g = ambient->Attribute("G") ? atof(ambient->Attribute("G")) : 50;
            auto b = ambient->Attribute("B") ? atof(ambient->Attribute("B")) : 50;
            float rgb[3] = {(float)r/255, (float)g/255, (float)b/255};
            reflection.ambient = Color(rgb[0], rgb[1], rgb[2]);
        }
        
        auto specular = element_material->FirstChildElement("specular");
        if (specular != nullptr){
            auto r = specular->Attribute("R") ? atof(specular->Attribute("R")) : 0;
            auto g = specular->Attribute("G") ? atof(specular->Attribute("G")) : 0;
            auto b = specular->Attribute("B") ? atof(specular->Attribute("B")) : 0;
            float rgb[3] = {(float)r/255, (float)g/255, (float)b/255};
            reflection.specular = Color(rgb[0], rgb[1], rgb[2]);
        }
        
        auto emissive = element_material->FirstChildElement("emissive");
        if (emissive != nullptr){
            auto r = emissive->Attribute("R") ? atof(emissive->Attribute("R")) : 0;
            auto g = emissive->Attribute("G") ? atof(emissive->Attribute("G")) : 0;
            auto b = emissive->Attribute("B") ? atof(emissive->Attribute("B")) : 0;
            float rgb[3] = {(float)r/255, (float)g/255, (float)b/255};
            reflection.emissive = Color(rgb[0], rgb[1], rgb[2]);
        }
        
        auto shininess = element_material->FirstChildElement("shininess");
        if (shininess != nullptr){
            auto value = shininess->Attribute("value") ? atof(shininess->Attribute("value")) : 0;
            reflection.shininess = value;
        }
        reflection.has_material = true;
        
    }
    return reflection;
}

auto Parser::parse_lights(XMLElement* element_lights) -> vector<Light>{
    vector<Light> lights_vec;
    if (element_lights == nullptr) return lights_vec;
    XMLElement* child_element = element_lights->FirstChildElement();
    while (child_element != nullptr){
        if (strcmp(child_element->Name(), "light") == 0){
            string type = child_element->Attribute("type") ? child_element->Attribute("type") : "ERROR";
            if (type == "point"){
                float x = child_element->Attribute("posx") ? atof(child_element->Attribute("posx")) : 0;
                float y = child_element->Attribute("posy") ? atof(child_element->Attribute("posy")) : 10;
                float z = child_element->Attribute("posz") ? atof(child_element->Attribute("posz")) : 0;
                lights_vec.push_back(Light(Point(x, y, z)));
            }
            else if( type == "directional"){
                float x = child_element->Attribute("dirx") ? atof(child_element->Attribute("dirx")) : 1;
                float y = child_element->Attribute("diry") ? atof(child_element->Attribute("diry")) : 1;
                float z = child_element->Attribute("dirz") ? atof(child_element->Attribute("dirz")) : 1;
                lights_vec.push_back(Light(0,Point(x, y, z)));
            }
            else if( type == "spot"){
                float x = child_element->Attribute("posx") ? atof(child_element->Attribute("posx")) : 0;
                float y = child_element->Attribute("posy") ? atof(child_element->Attribute("posy")) : 10;
                float z = child_element->Attribute("posz") ? atof(child_element->Attribute("posz")) : 0;
                float dx = child_element->Attribute("dirx") ? atof(child_element->Attribute("dirx")) : 1;
                float dy = child_element->Attribute("diry") ? atof(child_element->Attribute("diry")) : 1;
                float dz = child_element->Attribute("dirz") ? atof(child_element->Attribute("dirz")) : 1;
                float cutoff = child_element->Attribute("cutoff") ? atof(child_element->Attribute("cutoff")) : 45;
                lights_vec.push_back(Light(Point(x, y, z), Point(dx, dy, dz), cutoff));
            }
        }
        child_element = child_element->NextSiblingElement();
    }
    return lights_vec;
}


auto Parser::parse() -> Scene {
    XMLDocument doc;

    XMLError eResult = doc.LoadFile(this->file.c_str());
	if (eResult != XML_SUCCESS) throw runtime_error("Error loading file");
    
    XMLNode* root = doc.FirstChildElement("world");

    auto window = root->FirstChildElement("window");
	auto screen_width = stoi(window->Attribute("width") ? window->Attribute("width") : "512");
	auto screen_height = stoi(window->Attribute("height") ? window->Attribute("height") : "512");

    auto lights_element = root->FirstChildElement("lights");
    vector<Light> lights_vec = parse_lights(lights_element);

    XMLElement* child_element = root->FirstChildElement();
    Scene scene;
    scene.lights = lights_vec;

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
