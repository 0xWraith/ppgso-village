//
// Created by marek on 12. 12. 2023.
//

#ifndef PPGSO_RAVEN_H
#define PPGSO_RAVEN_H

#include <ppgso/ppgso.h>

#include "src/scene/scene.h"
#include "src/object/object.h"
#include "src/utils/utils.h"

class Raven final : public Object {
private:
    glm::vec3 speed;
    float animationTime = 0;
    int animationStep = 0;
    bool jumping = false;
public:
    Raven();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;

};


#endif //PPGSO_RAVEN_H
