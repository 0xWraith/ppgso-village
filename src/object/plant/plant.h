//
// Created by marek on 10. 12. 2023.
//

#ifndef PPGSO_PLANT_H
#define PPGSO_PLANT_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Plant final : public Object {
public:
    Plant();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};


#endif //PPGSO_PLANT_H
