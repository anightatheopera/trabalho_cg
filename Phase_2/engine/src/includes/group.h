#ifndef GROUP_H
#define GROUP_H

#include <vector>

#include "model.h"
#include "transformation.h"

class Group {

    public:
        std::vector<Group> subgroups;
        std::vector<Model> models;
        std::vector<Transformation> transformations;

        Group(std::vector<Group> subgroups, std::vector<Model> models, std::vector<Transformation> transformations);
        Group();

        auto show() -> void;
        auto addSubgroup(Group subgroup) -> void;
        auto addModel(Model model) -> void;
        auto addTransformation(Transformation transformation) -> void;
        auto applyTransformations();
        auto render() -> void;
        auto load_models() -> void;
};

#endif