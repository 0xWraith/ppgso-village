//
// Created by marek on 28. 11. 2023.
//

#ifndef PPGSO_FIRE_PIT_H
#define PPGSO_FIRE_PIT_H

#include "ppgso.h"

#include "src/scene/scene.h"
#include "src/object/object.h"

class FirePit final : public Object {
public:
    FirePit();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};


#endif //PPGSO_FIRE_PIT_H
