#ifndef PPGSO_FISHSPAWNER_H
#define PPGSO_FISHSPAWNER_H

#include <ppgso/ppgso.h>
#include <string>
#include "src/object/object.h"

class FishSpawner {
public:
    const std::string FISH_OBJECT_MODELS[3] = {
            "models/fish1.obj",
            "models/fish2.obj",
            "models/fish3.obj"
    };
    const std::string FISH_OBJECT_TEXTURES[3] = {
            "textures/fish1.bmp",
            "textures/fish2.bmp",
            "textures/fish3.bmp"
    };
    glm::vec3 FISH_OBJECT_SCALES[3] = {
            glm::vec3 {0.5, 0.5, 0.5},
            glm::vec3 {0.1, 0.1, 0.1},
            glm::vec3 {0.5, 0.5, 0.5}
    };
    const float BUCKET_FISH_SPAWN_INTERVAL = 10.0f;
    const float LAKE_FISH_SPAWN_INTERVAL = 5.0f;

    static constexpr const float BUCKET_FISH_PATH_TIME_INTERVAL = 2.5f;
    static constexpr const float LAKE_FISH_PATH_TIME_INTERVAL = 1.0f;
private:
    float bucketFishSpawnInterval = 0.0f;
    float lakeFishSpawnTime = 0.0f;
public:
    FishSpawner();
    bool update(Scene &scene, float dt);
};

#endif //PPGSO_FISHSPAWNER_H
