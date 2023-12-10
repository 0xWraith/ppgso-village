//
// Created by marek on 10. 12. 2023.
//

#ifndef PPGSO_WHEAT_H
#define PPGSO_WHEAT_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"


class Wheat : public Object {
public:
    Wheat();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;

};


#endif //PPGSO_WHEAT_H
