//
// Created by wraith on 10.11.2023.
//

#ifndef PPGSO_GRASS_H
#define PPGSO_GRASS_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Grass final : public Object {
public:
    Grass(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
