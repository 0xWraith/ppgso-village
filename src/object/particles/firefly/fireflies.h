//
// Created by wraith on 12/1/2023.
//

#ifndef PPGSO_FIREFLIES_H
#define PPGSO_FIREFLIES_H

#include "src/scene/Scene.h"
#include "src/object/object.h"

class FireFly final : public Object {
public:
    int lightIndex = -1;
    glm::vec3 speed;
    glm::vec3 color;
    float lifeTime = 0.0f;
    bool isStatic = false;
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
    FireFly(glm::vec3 position);
};


#endif //PPGSO_FIREFLIES_H
