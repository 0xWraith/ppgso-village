//
// Created by marek on 10. 12. 2023.
//

#ifndef PPGSO_SCARECROW_H
#define PPGSO_SCARECROW_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Scarecrow : public Object {
public:
    Scarecrow();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;

};


#endif //PPGSO_SCARECROW_H
