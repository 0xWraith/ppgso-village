#ifndef PPGSO_TREE_H
#define PPGSO_TREE_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Tree final : public Object {
public:
    Tree(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
