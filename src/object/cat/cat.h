#ifndef PPGSO_CAT_H
#define PPGSO_CAT_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Cat final : public Object {
public:
    std::unique_ptr<ppgso::Texture> shadow_map;
    float animationTime = 0;
    int animationStep = 0;
public:
    Cat(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
