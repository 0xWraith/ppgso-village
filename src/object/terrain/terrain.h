//
// Created by wraith on 10.11.2023.
//

#ifndef PPGSO_TERRAIN_H
#define PPGSO_TERRAIN_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Terrain final : public Object {
public:
    Terrain(const std::string model, const std::string texture);
    Terrain(const std::string model);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
