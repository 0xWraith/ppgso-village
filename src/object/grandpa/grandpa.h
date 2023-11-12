#ifndef PPGSO_GRANDPA_H
#define PPGSO_GRANDPA_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Grandpa final : public Object {
public:
    std::unique_ptr<ppgso::Texture> shadow_map;
public:
    Grandpa(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
