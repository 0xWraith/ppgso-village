#ifndef PPGSO_DOG_H
#define PPGSO_DOG_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Dog final : public Object {
public:
    std::unique_ptr<ppgso::Texture> shadow_map;
    std::vector<glm::vec3> path_points = {
            glm::vec3(-10.2, 4.21322, 100.529),
            glm::vec3(-10.5017, 9.85349, 105.684),
            glm::vec3(-10.2244, 0.580715, 126.413),
            glm::vec3(-9.52844, -14.2312, 140.217),
            glm::vec3(-9.12481, -28.2469, 154.227),
            glm::vec3(-8.78405, -40.0793, 166.055)
    };
    float currentTimeInPath = 0.0f;
public:
    Dog(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
