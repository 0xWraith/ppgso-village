//
// Created by marek on 11. 12. 2023.
//

#ifndef PPGSO_PICKAXE_H
#define PPGSO_PICKAXE_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Pickaxe final : public Object {
public:
    Pickaxe();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;

};


#endif //PPGSO_PICKAXE_H
