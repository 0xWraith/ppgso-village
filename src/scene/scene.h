//
// Created by wraith on 02.11.2023.
//

#ifndef PPGSO_SCENE_H
#define PPGSO_SCENE_H

#include "src/camera/camera.h"
#include "src/object/object.h"
#include <vector>
#include <list>

class Scene {
private:
    std::list<std::unique_ptr<Object>> objects;
    std::unique_ptr<Camera> camera;
public:
    void render();
    void update(float time);
};

#endif //PPGSO_SCENE_H
