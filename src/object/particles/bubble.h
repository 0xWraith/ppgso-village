//
// Created by wraith on 18.11.2023.
//

#ifndef PPGSO_BUBBLE_H
#define PPGSO_BUBBLE_H


#include "src/scene/Scene.h"
#include "src/object/object.h"

class Bubble final : public Object {
public:
    glm::vec3 speed;
    glm::vec3 color;
    float lifeTime = 0.0f;
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
    Bubble(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 speed);
};


#endif //PPGSO_BUBBLE_H
