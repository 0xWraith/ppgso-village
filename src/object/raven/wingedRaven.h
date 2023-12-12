//
// Created by marek on 12. 12. 2023.
//

#ifndef PPGSO_WINGEDRAVEN_H
#define PPGSO_WINGEDRAVEN_H

#include <ppgso/ppgso.h>

#include "src/scene/scene.h"
#include "src/object/object.h"
#include "src/utils/utils.h"

class WingedRaven final : public Object {
private:
    glm::vec3 speed;
    float animationTime = 0;
    int animationStep = 0;
    bool jumping = false;

public:
    WingedRaven();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;

};


#endif //PPGSO_WINGEDRAVEN_H
