//
// Created by marek on 28. 11. 2023.
//

#ifndef PPGSO_TREE_LOG_H
#define PPGSO_TREE_LOG_H

#include "ppgso.h"

#include "src/scene/scene.h"
#include "src/object/object.h"

class TreeLog final : public Object {
public:
    TreeLog();
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};


#endif //PPGSO_TREE_LOG_H
