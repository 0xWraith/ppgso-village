#ifndef PPGSO_GARDEN_H
#define PPGSO_GARDEN_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Garden final : public Object {
public:
    std::unique_ptr<ppgso::Texture> shadow_map;
public:
    Garden(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
