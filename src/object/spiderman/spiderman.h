//
// Created by marek on 12. 12. 2023.
//

#ifndef PPGSO_SPIDERMAN_H
#define PPGSO_SPIDERMAN_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Spiderman final : public Object {
public:
    Spiderman();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;

};


#endif //PPGSO_SPIDERMAN_H
