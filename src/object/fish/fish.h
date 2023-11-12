#ifndef PPGSO_FISH_H
#define PPGSO_FISH_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Fish final : public Object {
public:
    std::unique_ptr<ppgso::Texture> shadow_map;
public:
    Fish(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
