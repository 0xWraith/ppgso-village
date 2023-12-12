#ifndef PPGSO_FIRE_H
#define PPGSO_FIRE_H

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Fire final : public Object {
public:
    glm::vec3 speed;
    glm::vec3 color;
    float lifeTime = 0.0f;
    Fire(glm::vec3 speed, int color, float lifetime);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};


#endif //PPGSO_FIRE_H
