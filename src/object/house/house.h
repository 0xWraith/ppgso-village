//
// Created by wraith on 10.11.2023.
//

#ifndef PPGSO_HOUSE_H
#define PPGSO_HOUSE_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class House final : public Object {
public:
    House(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
