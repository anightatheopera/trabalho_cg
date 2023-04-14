#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <string>

#include "model.h"
#include "transformation.h"

class Group {

    public:
	std::string name;
        std::vector<Group> subgroups;
        std::vector<Model> models;
        std::vector<Transformation> transformations;

        Group(std::vector<Group> subgroups, std::vector<Model> models, std::vector<Transformation> transformations, std::string name);
        Group();

        auto show() -> void;
        auto pprint(int ident) -> void;
        auto pprint() -> void;
	auto set_name(std::string name) -> void;
        auto addSubgroup(Group subgroup) -> void;
        auto addModel(Model model) -> void;
        auto addTransformation(Transformation transformation) -> void;
        auto applyTransformations();
        auto render(bool picker = false) -> void;
        auto load_models() -> void;
};

#endif
