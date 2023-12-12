//
// Created by marek on 12. 12. 2023.
//

#ifndef PPGSO_JUMPINGRAVEN_H
#define PPGSO_JUMPINGRAVEN_H

#include <ppgso/ppgso.h>

#include "src/scene/scene.h"
#include "src/object/object.h"

class JumpingRaven  final : public Object {
private:
    glm::vec3 speed;
    float animationTime = 0;
    bool jumping = false;

public:
    JumpingRaven();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};


#endif //PPGSO_JUMPINGRAVEN_H
