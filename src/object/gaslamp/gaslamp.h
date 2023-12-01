#ifndef PPGSO_GASLAMP_H
#define PPGSO_GASLAMP_H

#include <ppgso/ppgso.h>
#include "src/scene/Scene.h"
#include "src/object/object.h"

class GasLamp final : public Object {
public:
    GasLamp();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};

#endif //PPGSO_GASLAMP_H
