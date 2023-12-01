#ifndef PPGSO_GASLAMPLIGHT_H
#define PPGSO_GASLAMPLIGHT_H

#include <ppgso/ppgso.h>
#include "src/scene/Scene.h"
#include "src/object/object.h"

class GasLampLight  final : public Object {
    glm::vec3 color;
public:
    GasLampLight(glm::vec3 color);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};


#endif //PPGSO_GASLAMPLIGHT_H
