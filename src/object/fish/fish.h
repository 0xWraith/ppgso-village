#ifndef PPGSO_FISH_H
#define PPGSO_FISH_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Fish final : public Object {
public:
    enum ENUM_FISH_TYPE {
        WATER_FISH,
        BUCKET_FISH
    };
    std::vector<glm::vec3> BUCKET_FISH_PATH_POINTS = {
            {0.198704, 4.53064, 100.736},
            {-0.621953, 24.751, 102.943},
            {-0.872804, 13.4542, 133.966},
            {-0.542558, -10.8845, 155.974},
            {-1.60295, -31.1129, 174.94},
            {-2.11358, -40.8538, 184.073}
    };
    bool test = false;
    std::vector<glm::vec3> LAKE_FISH_PATH_POINTS;
    ENUM_FISH_TYPE fishType;
    float currentTimeInPath = 0.0f;
    std::unique_ptr<ppgso::Texture> shadow_map;
public:
    Fish(const std::string model, const std::string texture, ENUM_FISH_TYPE fishType);
    Fish(const std::string model, const std::string texture, glm::vec3 position, glm::vec3 rotation, ENUM_FISH_TYPE fishType);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
