//
// Created by wraith on 02.11.2023.
//

#ifndef PPGSO_SCENE_H
#define PPGSO_SCENE_H

#include "src/object/treeStruct.h"
#include "src/camera/camera.h"
#include "src/object/object.h"
#include "src/object/fish/fishSpawner.h"
#include "src/camera/cinematic/cinematic.h"
#include <vector>
#include <list>
#include <map>
#include <src/utils/config/config.h>
struct Light {
    glm::vec3 position;
    glm::vec3 color;
    float range;
    float strength;
};

class Scene {
public:

    bool DAY_TIME = Config::DAY_TIME;
    bool GLOBAL_LIGHTING_ON = true;
    glm::vec3 LIGHT_DIRECTION = {0.25 , 1, 0.5};

    constexpr static const int MAX_WHEATS = 80;
    constexpr static const int RAVENS = 13;
    constexpr static const int FLYING_RAVENS = 5;

    constexpr static const float CAMERA_SPEED = 15.0f;
    std::shared_ptr<treeStruct> sceneStructure;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<FishSpawner> fishSpawner;
    std::unique_ptr<Cinematic> cinematic;
    std::map<int, int> keyboard;
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int cubeVAO, cubeVBO;
    std::unique_ptr<ppgso::Shader> skyboxShader;
    unsigned int cubemapTexture;

    int lightCount = 0;
    Light lights[200];

private:
    void generateSkybox();
    void initCinematic();
    void initLights();
    void generateWheatField(std::shared_ptr<treeStruct> fieldStruct);

public:
    void init();
    void render();
    void update(float time);
};

#endif //PPGSO_SCENE_H
