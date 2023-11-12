#ifndef PPGSO_DOG_H
#define PPGSO_DOG_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Dog final : public Object {
public:
    std::unique_ptr<ppgso::Texture> shadow_map;
public:
    Dog(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
