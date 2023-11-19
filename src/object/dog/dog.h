#ifndef PPGSO_DOG_H
#define PPGSO_DOG_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Dog final : public Object {
public:
    std::unique_ptr<ppgso::Texture> shadow_map;
    std::vector<glm::vec3> path_points = {
            glm::vec3(39.4554, 6.75454, -35.1547),
            glm::vec3(56.812, 6.08501, -50.8553),
            glm::vec3(40.6432, 7.01421, -65.0723),
            glm::vec3(23.7818, 7.76478, -52.1277),
            glm::vec3(39.4554, 6.75454, -35.1547)
    };
    float currentTimeInPath = 0.0f;
public:
    Dog(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
