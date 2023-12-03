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

struct Light {
    glm::vec3 position;
    glm::vec3 color;
    float range;
    float strength;
};

class Scene {
public:

    bool DAY_TIME = false;
    bool GLOBAL_LIGHTING_ON = true;
    glm::vec3 LIGHT_DIRECTION = {0.25 , 1, 0.5};

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

    unsigned int FBO;
    unsigned int framebufferTexture;
    unsigned int rectangleVAO, rectangleVBO;

    int lightCount = 0;
    Light lights[200];

private:
    void generateSkybox();
    void initCinematic();
    void initLights();

public:
    void init();
    void render();
    void update(float time);
};

#endif //PPGSO_SCENE_H
