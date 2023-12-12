
#ifndef PPGSO_STATICRAVEN_H
#define PPGSO_STATICRAVEN_H

#include <ppgso/ppgso.h>

#include "src/scene/scene.h"
#include "src/object/object.h"

class StaticRaven final : public Object {

public:
    StaticRaven();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;

};


#endif //PPGSO_STATICRAVEN_H
