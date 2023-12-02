#include "fishSpawner.h"

#include "src/object/fish/fish.h"
#include "src/utils/utils.h"

FishSpawner::FishSpawner() {

}

bool FishSpawner::update(Scene &scene, float dt) {
    lakeFishSpawnTime += dt;
    bucketFishSpawnInterval += dt;
    int randomFish = Utils::randomInt(0, 2);

    if (bucketFishSpawnInterval >= BUCKET_FISH_SPAWN_INTERVAL) {
        bucketFishSpawnInterval = 0.0f;

        std::shared_ptr<treeStruct> fish = std::make_shared<treeStruct>("fish1", std::move(std::make_unique<Fish>(FISH_OBJECT_MODELS[randomFish], FISH_OBJECT_TEXTURES[randomFish],
                                                                                                                  Fish::ENUM_FISH_TYPE::BUCKET_FISH)),
                                                                         glm::vec3 {0.0, 5.0, 100.0},
                                                                         glm::vec3 {glm::radians(45.0), 0, 0},
                                                                         FISH_OBJECT_SCALES[randomFish]);
        ((Fish*)fish->obj.get())->fishType = Fish::ENUM_FISH_TYPE::BUCKET_FISH;
        scene.sceneStructure->addChild(fish);
    }

    if (lakeFishSpawnTime >= LAKE_FISH_SPAWN_INTERVAL) {
        lakeFishSpawnTime = 0.0f;
        auto randomAngle = (float)Utils::randomInt(0, 360);
        glm::vec3 position = Utils::getPointTowards(glm::vec3 {0.0, -33, 270.0}, randomAngle, 90.0f);

        std::shared_ptr<treeStruct> fish = std::make_shared<treeStruct>("bruh_fish", std::move(std::make_unique<Fish>(FISH_OBJECT_MODELS[randomFish], FISH_OBJECT_TEXTURES[randomFish], position, glm::vec3 {glm::radians(45.0), randomAngle, 0}, Fish::ENUM_FISH_TYPE::WATER_FISH)),
                                                                        position,
                                                                        glm::vec3 {glm::radians(45.0), randomAngle, 0},
                                                                        FISH_OBJECT_SCALES[randomFish]);
        scene.sceneStructure->addChild(fish);
    }
    return true;
}
