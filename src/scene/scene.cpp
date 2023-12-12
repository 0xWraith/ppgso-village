#include "scene.h"
#include <shaders/skybox_vert_glsl.h>
#include <shaders/skybox_frag_glsl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "src/object/bucket/bucket.h"
#include "src/object/cat/cat.h"
#include "src/object/dog/dog.h"
#include "src/object/fish/fish.h"
#include "src/object/terrain/terrain.h"
#include "src/object/house/house.h"
#include "src/object/tree/tree.h"
#include "src/object/treeStruct.h"
#include "src/object/particles/bubble.h"
#include "src/object/gaslamp/gaslamp.h"
#include "src/object/gaslamp/gaslamplight.h"
#include "src/object/particles/firefly/fireflies.h"
#include "src/utils/config/config.h"
#include "src/utils/utils.h"
#include "src/object/particles/fire/fire.h"
#include "src/object/fire_pit/fire_pit.h"
#include "src/object/tree_log/tree_log.h"
#include "src/object/plant/plant.h"
#include "src/object/wheat/wheat.h"
#include "src/object/scarecrow/scarecrow.h"
#include "src/object/pickaxe/pickaxe.h"
#include "src/object/raven/raven.h"
#include "src/object/raven/wingedRaven.h"
#include "src/object/raven/staticRaven.h"
#include "src/object/raven/jumpingRaven.h"


void printSceneInitProgress(int progress, int max);
void generateWheatField(std::shared_ptr<treeStruct> fieldStruct);

float camPosX, camPosY, camPosZ;

float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
float skyboxVertices[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
};

float fireParticleSpawnTime = 0.0f;

void Scene::update(float time) {

    fireParticleSpawnTime += time;

    if (fireParticleSpawnTime >= 0.2f) {
        fireParticleSpawnTime = 0.0f;

        for (int i = 0; i < 4; i++) {
            std::shared_ptr<treeStruct> fire = std::make_shared<treeStruct>(
                    "fire_" + std::to_string(Utils::randomInt(1, 1000)), std::move(std::make_unique<Fire>(
                            glm::vec3(Utils::randomInt(-2, 2), Utils::randomInt(1, 4), Utils::randomInt(-2, 2)),
                            1, Utils::randomInt(1, 4))),
                    glm::vec3{-43.5, 5.7, 35.5}, glm::vec3{0, 0, 0}, glm::vec3{0.05, 0.15, 0.05});
            sceneStructure->addChild(fire);
        }
        for (int i = 0; i < 3; i++) {
            std::shared_ptr<treeStruct> fire = std::make_shared<treeStruct>(
                    "fire_" + std::to_string(Utils::randomInt(1, 1000)), std::move(std::make_unique<Fire>(
                            glm::vec3(Utils::randomInt(-3, 3), Utils::randomInt(1, 2), Utils::randomInt(-3, 3)),
                            2, Utils::randomInt(1, 2))),
                    glm::vec3{-43.5, 5.7, 35.5}, glm::vec3{0, 0, 0}, glm::vec3{0.45, 0.45, 0.45});
            sceneStructure->addChild(fire);
        }
        for (int i = 0; i < 2; i++) {
            std::shared_ptr<treeStruct> fire = std::make_shared<treeStruct>(
                    "fire_" + std::to_string(Utils::randomInt(1, 1000)), std::move(std::make_unique<Fire>(
                            glm::vec3(Utils::randomInt(-3, 3), Utils::randomInt(1, 2), Utils::randomInt(-3, 3)),
                            3, 0.6)),
                    glm::vec3{-43.5, 5.7, 35.5}, glm::vec3{0, 0, 0}, glm::vec3{0.6, 1, 0.6});
            sceneStructure->addChild(fire);
        }
    }


    sceneStructure->update(*this, time);

    float speed = time * CAMERA_SPEED;

    if (keyboard[GLFW_KEY_LEFT_CONTROL]) {
        speed *= 10 ;
    }

    if (keyboard[GLFW_KEY_W]) {
        camera->position += camera->cameraFront * speed;
    }
    if (keyboard[GLFW_KEY_S]) {
        camera->position -= camera->cameraFront * speed;
    }
    if (keyboard[GLFW_KEY_A]) {
        camera->position -= glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * speed;
    }
    if (keyboard[GLFW_KEY_D]) {
        camera->position += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * speed;
    }
    if(keyboard[GLFW_KEY_SPACE]) {
        camera->position += camera->cameraUp * speed;
    }
    if(keyboard[GLFW_KEY_LEFT_SHIFT]) {
        camera->position -= camera->cameraUp * speed;
    }
    if (keyboard[GLFW_KEY_0] && (camPosX != camera->position.x && camPosY != camera->position.y && camPosZ != camera->position.z)) {
        camPosX = camera->position.x;
        camPosY = camera->position.y;
        camPosZ = camera->position.z;
        std::cout << "glm::vec3(" << camera->position.x << ", " << camera->position.y << ", " << camera->position.z << ")," << std::endl;
    }
    if (keyboard[GLFW_KEY_9]) {
        if (!cinematic->isStarted()) {
            cinematic->start(*this);
        }
    }
    if (keyboard[GLFW_KEY_8]) {
        cinematic->stop();
    }
    if (keyboard[GLFW_KEY_B] == GLFW_PRESS) {
        Config::CONFIG_BLOOM = !Config::CONFIG_BLOOM;
        keyboard[GLFW_KEY_B] = GLFW_RELEASE;
    }
    if (keyboard[GLFW_KEY_N] == GLFW_PRESS) {
        Config::CONFIG_NOISE = !Config::CONFIG_NOISE;
        keyboard[GLFW_KEY_N] = GLFW_RELEASE;
    }

    glDepthFunc(GL_LEQUAL);

    skyboxShader->use();

    skyboxShader->setUniform("view", glm::mat4(glm::mat3(camera->viewMatrix)));
    skyboxShader->setUniform("projection", camera->projectionMatrix);
    skyboxShader->setUniform("model", glm::mat4(1.0f));


    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);

    this->camera->update();
    fishSpawner->update(*this, time);

    if (cinematic->isStarted()) {
        cinematic->update(*this, time);
    }
}

void Scene::render() {
    if(sceneStructure) {
        sceneStructure->render(*this);
    }
}

void Scene::init() {
    int progress = 0;
    const int maxProgress = 68;

    generateSkybox();
    printSceneInitProgress(++progress, maxProgress);

    initCinematic();
    printSceneInitProgress(++progress, maxProgress);

    camera = std::make_unique<Camera>();
    printSceneInitProgress(++progress, maxProgress);

    fishSpawner = std::make_unique<FishSpawner>();
    printSceneInitProgress(++progress, maxProgress);

    sceneStructure = std::make_shared<treeStruct>("scene1");
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> grass = std::make_shared<treeStruct>("grass", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/grass.bmp")),
                                                  glm::vec3 {0,0,0}, glm::vec3 {3*ppgso::PI/2, 0, 0}, glm::vec3 {0.5, 0.5, 0.5});
    sceneStructure->addChild(grass);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> house = std::make_shared<treeStruct>("house", std::move(std::make_unique<Terrain>("models/house.obj", "textures/house.bmp")),
                                                                     glm::vec3 {-43.1071, 3.80, -20.6743}, glm::vec3 {0 , 0, 0}, glm::vec3 {1,1,1});
    sceneStructure->addChild(house);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> tree = std::make_shared<treeStruct>("tree", std::move(std::make_unique<Terrain>("models/tree.obj", "textures/tree.bmp")),
                                                                    glm::vec3 {40.0, 3.5, -50.0}, glm::vec3 {3, 4.0, 3});
    sceneStructure->addChild(tree);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> cat = std::make_shared<treeStruct>("cat", std::move(std::make_unique<Cat>("models/cat.obj", "textures/cat.bmp")),
                                                                  glm::vec3 {45.5, 25.0, -49.7439},
                                                                  glm::vec3 {glm::radians(245.0),
                                                                             0,
                                                                             glm::radians(90.0)},
                                                                  glm::vec3 {0.1, 0.1, 0.1});

    sceneStructure->addChild(cat);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> sand = std::make_shared<treeStruct>("sand", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                    glm::vec3 {0.0, -0.5, 90.0}, glm::vec3 {3*ppgso::PI/2, 0, 0}, glm::vec3 {0.5, 0.1, 0.5});
    sceneStructure->addChild(sand);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> depthSand1 = std::make_shared<treeStruct>("depthSand1", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {0.0, -31.0, 133.0}, glm::vec3 {glm::radians(315.0), 0, 0}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand1);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> depthSand2 = std::make_shared<treeStruct>("depthSand2", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {-100.0, -31.0, 140.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0.0, glm::radians(45.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand2);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> depthSand3 = std::make_shared<treeStruct>("depthSand3", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {100.0, -31.0, 140.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0, glm::radians(-45.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand3);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> depthSand4 = std::make_shared<treeStruct>("depthSand4", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {-145, -31.0, 245.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0, glm::radians(90.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand4);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> depthSand5 = std::make_shared<treeStruct>("depthSand5", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {145, -31.0, 245.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0, glm::radians(-90.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand5);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> depthSand6 = std::make_shared<treeStruct>("depthSand6", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {-100, -31.0, 350.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0.0, glm::radians(135.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand6);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> depthSand7 = std::make_shared<treeStruct>("depthSand7", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {100, -31.0, 350.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0, glm::radians(-135.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand7);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> depthSand8 = std::make_shared<treeStruct>("depthSand8", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {0.0, -31.0, 390.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0, glm::radians(180.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand8);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> water = std::make_shared<treeStruct>("water", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/water.bmp")),
                                                                     glm::vec3 {0.0, -45, 250}, glm::vec3 {3*ppgso::PI/2, 0, 0}, glm::vec3 {1, 1, 1});
    ((Terrain*)water->obj.get())->type = Terrain::TERRAIN_TYPE::WATER;
    sceneStructure->addChild(water);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> dog = std::make_shared<treeStruct>("dog", std::move(std::make_unique<Dog>("models/dog.obj", "textures/dog.bmp")),
                                                                   glm::vec3 {-20, 10, 0}, glm::vec3 {glm::radians(270.0), 0, 0}, glm::vec3 {0.2, 0.2, 0.2});
    sceneStructure->addChild(dog);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> bucket = std::make_shared<treeStruct>("bucket", std::move(std::make_unique<Bucket>("models/bucket.obj", "textures/bucket.bmp")),
                                                                      glm::vec3 {0.0, 4.2, 101.0},
                                                                      glm::vec3 {glm::radians(0.0), 0, 0},
                                                                      glm::vec3 {0.25, 0.25, 0.25});
    sceneStructure->addChild(bucket);
    printSceneInitProgress(++progress, maxProgress);

//    std::shared_ptr<treeStruct> spiderman = std::make_shared<treeStruct>("spiderman", std::move(std::make_unique<Spiderman>()),
//                                                                         glm::vec3 {-10, 4.2, 101.0},
//                                                                         glm::vec3 {0, 0, 0},
//                                                                         glm::vec3 {2, 2, 2});
//    sceneStructure->addChild(spiderman);
//    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> waterInBucket1 = std::make_shared<treeStruct>("waterInBucket1", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/water.bmp")),
                                                                              glm::vec3 {0.0, 5.0, 101.0},
                                                                              glm::vec3 {3*ppgso::PI/2, 0, 0},
                                                                              glm::vec3 {0.005, 0.005, 0.005});
//    ((Terrain*)waterInBucket1->obj.get())->type = Terrain::TERRAIN_TYPE::WATER;
    sceneStructure->addChild(waterInBucket1);
    printSceneInitProgress(++progress, maxProgress);


    if(DAY_TIME == false) {
        std::shared_ptr<treeStruct> moon = std::make_shared<treeStruct>("moon", std::move(std::make_unique<Terrain>("models/moon.obj", "textures/moon.bmp")),glm::vec3{774.256, 1891.07, 1095.69}, glm::vec3{0, 0, 0}, glm::vec3{100, 100, 100});
        sceneStructure->addChild(moon);
    }

    initLights();
    printSceneInitProgress(++progress, maxProgress);

    for(int i = 0; i < 5; i++) {

        std::shared_ptr<treeStruct> gate_first_row = std::make_shared<treeStruct>("gate_first_row", std::move(std::make_unique<Terrain>("models/gate.obj", "textures/gate.bmp")),
                                                                                  glm::vec3 {-58.0 + (i * 27.6), 3.5, -70.0},
                                                                                  glm::vec3 {3 * ppgso::PI / 2, 0, 0},
                                                                                  glm::vec3 {0.1, 0.1, 0.1});
        sceneStructure->addChild(gate_first_row);
        printSceneInitProgress(++progress, maxProgress);

        std::shared_ptr<treeStruct> gate_third_row = std::make_shared<treeStruct>("gate_third_row", std::move(std::make_unique<Terrain>("models/gate.obj", "textures/gate.bmp")),
                                                                                  glm::vec3 {-72, 3.5, -56.0 + (i * 27.6)},
                                                                                  glm::vec3 {3 * ppgso::PI / 2, 0.0, ppgso::PI / 2},
                                                                                  glm::vec3 {0.1, 0.1, 0.1});
        sceneStructure->addChild(gate_third_row);
        printSceneInitProgress(++progress, maxProgress);

        std::shared_ptr<treeStruct> gate_fourth_row = std::make_shared<treeStruct>("gate_fourth_row", std::move(std::make_unique<Terrain>("models/gate.obj", "textures/gate.bmp")),
                                                                                   glm::vec3 {66, 3.5, -56.0 + (i * 27.6)},
                                                                                   glm::vec3 {3 * ppgso::PI / 2, 0.0, ppgso::PI / 2},
                                                                                   glm::vec3 {0.1, 0.1, 0.1});
        sceneStructure->addChild(gate_fourth_row);
        printSceneInitProgress(++progress, maxProgress);
    }

    std::shared_ptr<treeStruct> firePit = std::make_shared<treeStruct>("fire_pit", std::move(std::make_unique<FirePit>()),
                                                                        glm::vec3  {-43.5,5.35,35.5},
                                                                        glm::vec3  {0,0,0},
                                                                        glm::vec3 {3,4.5,3});
    std::shared_ptr<treeStruct> treeLog1 = std::make_shared<treeStruct>("log1", std::move(std::make_unique<TreeLog>()),
                                                                        glm::vec3 {0,.05,0},
                                                                        glm::vec3 {0,.02,14},
                                                                        glm::vec3 {0.5,1,1});
    std::shared_ptr<treeStruct> treeLog2 = std::make_shared<treeStruct>("log2", std::move(std::make_unique<TreeLog>()),
                                                                        glm::vec3 {0,.07,0},
                                                                        glm::vec3 {.5,.75,1});
    firePit->addChild(treeLog1);
    firePit->addChild(treeLog2);
    sceneStructure->addChild(firePit);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> field1 = std::make_shared<treeStruct>("field1", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                     glm::vec3 {-43.1071, 4, 10.6743}, glm::vec3 {3*ppgso::PI/2, 3*ppgso::PI/2, 0}, glm::vec3 {0.015, 0.05, 0.25});
    sceneStructure->addChild(field1);

    std::shared_ptr<treeStruct> plant1 = std::make_shared<treeStruct>("plant1", std::move(std::make_unique<Plant>()),
                                                                     glm::vec3 {-36.1071, 6, 9.5}, glm::vec3 {0,0, 6*ppgso::PI/2}, glm::vec3 {7,25,7});

    std::shared_ptr<treeStruct> plant2 = std::make_shared<treeStruct>("plant2", std::move(std::make_unique<Plant>()),
                                                                     glm::vec3 {-50.1071, 6, 11.5}, glm::vec3 {0,0,0}, glm::vec3 {7,35,7});

    sceneStructure->addChild(plant1);
    sceneStructure->addChild(plant2);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> field2 = std::make_shared<treeStruct>("field2", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                     glm::vec3 {-43.1071, 4.5, 16.6743}, glm::vec3 {3*ppgso::PI/2, 3*ppgso::PI/2, 0}, glm::vec3 {0.015, 0.05, 0.25});
    sceneStructure->addChild(field2);
    std::shared_ptr<treeStruct> plant3 = std::make_shared<treeStruct>("plant3", std::move(std::make_unique<Plant>()),
                                                                      glm::vec3 {-50.1071, 6, 15.5}, glm::vec3 {0,0,0}, glm::vec3 {7,30.5,7});
    std::shared_ptr<treeStruct> plant4 = std::make_shared<treeStruct>("plant4", std::move(std::make_unique<Plant>()),
                                                                      glm::vec3 {-36.1071, 6, 17.5}, glm::vec3 {0,0,6*ppgso::PI/2}, glm::vec3 {7,36.5,7});
    sceneStructure->addChild(plant3);
    sceneStructure->addChild(plant4);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> field3 = std::make_shared<treeStruct>("field3", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                     glm::vec3 {-43.1071, 4.25, 22.6743}, glm::vec3 {3*ppgso::PI/2, 3*ppgso::PI/2, 0}, glm::vec3 {0.015, 0.05, 0.25});
    sceneStructure->addChild(field3);
    std::shared_ptr<treeStruct> plant5 = std::make_shared<treeStruct>("plant5", std::move(std::make_unique<Plant>()),
                                                                      glm::vec3 {-50.1071, 6, 21.5}, glm::vec3 {0,0,0}, glm::vec3 {7,28,7});
    std::shared_ptr<treeStruct> plant6 = std::make_shared<treeStruct>("plant6", std::move(std::make_unique<Plant>()),
                                                                      glm::vec3 {-36.1071, 6, 23.5}, glm::vec3 {0,0,6*ppgso::PI/2}, glm::vec3 {7,26.5,7});
    sceneStructure->addChild(plant5);
    sceneStructure->addChild(plant6);
    printSceneInitProgress(++progress, maxProgress);



    std::shared_ptr<treeStruct> pickaxe = std::make_shared<treeStruct>("pickaxe", std::move(std::make_unique<Pickaxe>()),
                                                                       glm::vec3 {-36.1071, 9.85, 24.2}, glm::vec3 {0.15,-2.7,5*ppgso::PI/2}, glm::vec3 {5,5,5});
    sceneStructure->addChild(pickaxe);
    printSceneInitProgress(++progress, maxProgress);

    std::shared_ptr<treeStruct> wheat_field = std::make_shared<treeStruct>("wheat_field", glm::vec3 {30,1,40});
    sceneStructure->addChild(wheat_field);
    generateWheatField(wheat_field);

    printSceneInitProgress(++progress, maxProgress);

    for(int i = 0; i < RAVENS; i++) {
        std::shared_ptr<treeStruct> raven = std::make_shared<treeStruct>("raven", std::move(std::make_unique<Raven>()));
        wheat_field->addChild(raven);
        printSceneInitProgress(++progress, maxProgress);
    }


    for(int i = 0; i < FLYING_RAVENS; i++) {
        std::shared_ptr<treeStruct> wingedRaven = std::make_shared<treeStruct>("winged_raven", std::move(
                std::make_unique<WingedRaven>()));
        sceneStructure->addChild(wingedRaven);
        printSceneInitProgress(++progress, maxProgress);
    }

    std::shared_ptr<treeStruct> lakeRavens = std::make_shared<treeStruct>("lakeRavens", glm::vec3 {0.0, 0.0, 250});
    sceneStructure->addChild(lakeRavens);
    for(int i = 0; i < FLYING_RAVENS; i++) {
        std::shared_ptr<treeStruct> wingedRaven = std::make_shared<treeStruct>("winged_raven", std::move(
                std::make_unique<WingedRaven>()));
        lakeRavens->addChild(wingedRaven);
        printSceneInitProgress(++progress, maxProgress);
    }

    std::shared_ptr<treeStruct> tripleRaven = std::make_shared<treeStruct>("first_raven", std::move(
            std::make_unique<WingedRaven>()));
    std::shared_ptr<treeStruct> raven2 = std::make_shared<treeStruct>("second_raven", std::move(
            std::make_unique<StaticRaven>()), glm::vec3 {12,0,-10});
    std::shared_ptr<treeStruct> raven3 = std::make_shared<treeStruct>("third_raven", std::move(
            std::make_unique<StaticRaven>()), glm::vec3 {-12,0,-10});
    tripleRaven->addChild(raven2);
    tripleRaven->addChild(raven3);

    lakeRavens->addChild(tripleRaven);
    printSceneInitProgress(++progress, maxProgress);


    std::cout << "Scene init done" << std::endl;
}

void Scene::initCinematic() {
    cinematic = std::make_unique<Cinematic>();

    cinematic->addKeyframe(Keyframe {
        Keyframe::ENUM_KEYFRAME_TYPE::DYNAMIC,
            0.0f,
            15.0f,
            glm::vec3(-0.133243, 6.21597, 101.762),
            glm::vec3(1.18998, -28.3695, 250.112),
            glm::vec3(-35.6095, 11.6488, -35.7162),
            glm::vec3(51.9252, 26.1331, 29.1459),
    });

    cinematic->addKeyframe(Keyframe {
        Keyframe::ENUM_KEYFRAME_TYPE::DYNAMIC,
            0.0f,
            10.0f,
            glm::vec3(-35.1402, 6.40459, -30.098),
            glm::vec3(51.9602, 26.1707, 28.9937),
            glm::vec3(-43.615, 8.62424, -28.3976),
            glm::vec3(-43.8611, 8.96226, -49.6532),
    });

    cinematic->addKeyframe(Keyframe {
        Keyframe::ENUM_KEYFRAME_TYPE::DYNAMIC,
            0.0f,
            12.0f,
        glm::vec3(38.0467, 17.4796, -49.0753),
        glm::vec3(-44.0045, 8.93651, -49.7709),
        glm::vec3(40.7067, 26.7709, -48.5475),
        glm::vec3(56.7258, 16.3926, -22.184),
    });

    cinematic->addKeyframe(Keyframe {
        Keyframe::ENUM_KEYFRAME_TYPE::DYNAMIC,
            0.0f,
            13.0f,
        glm::vec3(29.9382, 12.2684, 39.8503),
        glm::vec3(56.7528, 16.3946, -22.1766),
        glm::vec3(29.9382, 12.2684, 39.8503),
        glm::vec3(-12.1735, 14.7763, 21.4883),
    });

    cinematic->addKeyframe(Keyframe {
        Keyframe::ENUM_KEYFRAME_TYPE::DYNAMIC,
            0.0f,
            10.0f,
        glm::vec3(-43.7376, 7.25267, 35.6176),
        glm::vec3(-12.7532, 14.7627, 21.8555),
        glm::vec3(-42.051, 7.47669, 17.7813),
        glm::vec3(-28.9961, 12.5465, 6.49965),
    });

    cinematic->addKeyframe(Keyframe {
        Keyframe::ENUM_KEYFRAME_TYPE::DYNAMIC,
            0.0f,
            15.0f,
        glm::vec3(-1.87679, 4.94877, 100.197),
        glm::vec3(-29.0714, 12.5362, 6.4285),
        glm::vec3(-0.67319, 5.40559, 99.3626),
        glm::vec3(-5.57135, 5.39431, 102.007),
    });

    cinematic->addKeyframe(Keyframe {
        Keyframe::ENUM_KEYFRAME_TYPE::DYNAMIC,
            0.0f,
            10.0f,
        glm::vec3(-1.86219, -33.7992, 176.972),
        glm::vec3(-5.50081, 7.49312, 102.294),
        glm::vec3(0.124206, -34.1696, 176.577),
        glm::vec3(-10.5564, -17.4693, 206.464),
    });

    cinematic->addKeyframe(Keyframe {
            Keyframe::ENUM_KEYFRAME_TYPE::STATIC,
            0.0f,
            15.0f,
            glm::vec3(0.124206, -34.1696, 176.577),
            glm::vec3(-10.5564, -17.4693, 206.464),
            glm::vec3(0.124206, -34.1696, 176.577),
            glm::vec3(-10.5564, -17.4693, 206.464),
    });

    cinematic->addKeyframe(Keyframe {
            Keyframe::ENUM_KEYFRAME_TYPE::STATIC,
            0.0f,
            30.0f,
            glm::vec3(-56.2377, -30.2326, 264.54),
            glm::vec3(49.7615, -16.3351, 164.402),
            glm::vec3(-56.2377, -30.2326, 264.54),
            glm::vec3(71.623, -3.75438, 396.687),
    });

    cinematic->addKeyframe(Keyframe {
            Keyframe::ENUM_KEYFRAME_TYPE::STATIC,
            0.0f,
            60.0f,
            glm::vec3(-56.2377, -30.2326, 264.54),
            glm::vec3(71.623, -3.75438, 396.687),
            glm::vec3(-56.2377, -30.2326, 264.54),
            glm::vec3(71.623, -3.75438, 396.687),
    });


}

void Scene::generateSkybox() {
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));


    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    std::string skyBoxTextures[6] = {
            DAY_TIME ? "textures/skybox/graycloud_lf.jpg" : "textures/skybox/xneg.jpg",
            DAY_TIME ? "textures/skybox/graycloud_rt.jpg" : "textures/skybox/xpos.jpg",
            DAY_TIME ? "textures/skybox/graycloud_up.jpg" : "textures/skybox/ypos.jpg",
            DAY_TIME ? "textures/skybox/graycloud_dn.jpg" : "textures/skybox/yneg.jpg",
            DAY_TIME ? "textures/skybox/graycloud_ft.jpg" : "textures/skybox/zpos.jpg",
            DAY_TIME ? "textures/skybox/graycloud_bk.jpg" : "textures/skybox/zneg.jpg"
    };
    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

    for (unsigned int i = 0; i < 6; i++) {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(skyBoxTextures[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            std::cout << "Loaded texture: " << skyBoxTextures[i] << std::endl;
            std::cout << "Width: " << width << std::endl;
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,GL_RGB, width, height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Failed to load texture: " << skyBoxTextures[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    skyboxShader = std::make_unique<ppgso::Shader>(skybox_vert_glsl, skybox_frag_glsl);
    skyboxShader->use();

    skyboxShader->setUniform("skybox", 0);
}

void Scene::initLights() {

    if (DAY_TIME == true) {
        lights[lightCount].position = {666.655, 1654.05, 967.464};
        lights[lightCount].color = {130 / 255.0, 180 / 255.0, 255 / 255.0};
        lights[lightCount].range = 5000.0f;
        lights[lightCount++].strength = 5.f;
    } else {
        lights[lightCount].position = {666.655, 1654.05, 967.464};
        lights[lightCount].color = {29 / 255.0, 78 / 255.0, 105 / 255.0};
        lights[lightCount].range = 5000.0f;
        lights[lightCount++].strength = 3.5f;
    }

    lights[lightCount].position = glm::vec3(633.615, 1729.08, 979.094);
    lights[lightCount].color = {255 / 255.0, 255 / 255.0, 255 / 255.0};
    lights[lightCount].range = 300.0f;
    lights[lightCount++].strength = 10.5f;

    lights[lightCount].position = glm::vec3(-43.5, 6.7, 35.5);
    lights[lightCount].color = {255 / 255.0, 106 / 255.0, 20 / 255.0};
    lights[lightCount].range = 40.0f;
    lights[lightCount++].strength = 10.0f;

    glm::vec3 gasLampPositions[] = {
            glm::vec3(-35.0, 5, -30.0),
            glm::vec3(-50.0, 5, -30.0),
            glm::vec3(-3.62255, 3, 99.046),
            glm::vec3(24.4515, 6.15476, 45.9177),
            glm::vec3(37.3796, 5.10996, -46.4953),
            glm::vec3(-34.5537, 5.92026, 15.083),
            glm::vec3(-33.2405, 3.99544, -5.71075),
            glm::vec3(8.48522, 6.16977, 18.2136),
            glm::vec3(-54.844, 4.79072, 58.8602),
            glm::vec3(51.6863, 6.55078, 19.0941),
    };

    for(int i = 0; i < sizeof gasLampPositions / sizeof gasLampPositions[0]; i++) {

        lights[lightCount].position = gasLampPositions[i];
        lights[lightCount].position.y += 2.5;
        lights[lightCount].color = {255 / 255.0, 136 / 255.0, 49 / 255.0};
        lights[lightCount].range = 40.0f;
        lights[lightCount++].strength = 10.0f;

        std::cout << lights[lightCount - 1].position.x << " " << lights[lightCount - 1].position.y << " " << lights[lightCount - 1].position.z << std::endl;

        std::shared_ptr<treeStruct> gaslamp = std::make_shared<treeStruct>("gaslamp" + std::to_string(i), std::move(std::make_unique<Terrain>("models/lamp.obj", "textures/lamp.bmp")),gasLampPositions[i], glm::vec3 {0, 0, 0}, glm::vec3 {0.5, 0.5, 0.5});
        sceneStructure->addChild(gaslamp);

        std::shared_ptr<treeStruct> gaslampLight = std::make_shared<treeStruct>("gaslamplight" + std::to_string(i), std::move(std::make_unique<GasLampLight>(lights[2 + i].color)),glm::vec3 {0, 2.5, 0}, glm::vec3 {0, 0, 0}, glm::vec3 {2, 2, 2});
        sceneStructure->addObject("gaslamp" + std::to_string(i), gaslampLight);
    }

    glm::vec3 fireFlyPositions[] = {
            glm::vec3(9.50813, -29.5915, 190.738),
            glm::vec3(-2.46337, -29.6867, 189.801),
            glm::vec3(2.64814, -29.7984, 179.426),
            glm::vec3(-4.88798, -29.9024, 175.718),
            glm::vec3(-10.4234, -29.8597, 181.42),
            glm::vec3(-15.3347, -29.7982, 188.152),
            glm::vec3(-8.99411, -30.0039, 170.527),
            glm::vec3(-0.71694, -30.0964, 159.978),
            glm::vec3(5.15564, 6.80689, 99.0572),
            glm::vec3(3.08399, 10.2196, 95.7675),
            glm::vec3(-5.40658, 9.04207, 100.853),
            glm::vec3(-30.7219, 9.54831, 32.9077),
            glm::vec3(-34.171, 9.40399, 28.0117),
            glm::vec3(-42.4676, 11.9047, 18.8778),
            glm::vec3(-40.0924, 10.5001, 14.0319),
            glm::vec3(-43.7085, 13.4288, 24.5936),
            glm::vec3(-46.5199, 11.0057, 23.8322),
            glm::vec3(34.8757, 18.8523, 26.3807),
            glm::vec3(20.5361, 18.0733, 30.9947),
            glm::vec3(17.5839, 16.3782, 38.4387),
            glm::vec3(17.6118, 16.3058, 38.7427),
            glm::vec3(29.7771, 14.9424, 43.3944),
            glm::vec3(40.112, 15.1658, 50.5876),
            glm::vec3(52.9721, 15.5225, 58.0264),
            glm::vec3(-48.709, 11.0335, -32.8438),
            glm::vec3(-42.9121, 10.4588, -32.2022),
            glm::vec3(-42.4111, 15.1952, -39.1636),
            glm::vec3(-43.0609, 18.8065, -35.921),
            glm::vec3(35.4078, 12.6517, -45.6252),
            glm::vec3(37.9286, 16.1501, -56.2499),
            glm::vec3(47.0212, 30.0204, -55.4834),
            glm::vec3(45.8778, 29.1961, -45.4435),
            glm::vec3(-38.1072, 13.1497, -31.374),
            glm::vec3(-42.7643, 12.2611, -31.4715),
            glm::vec3(-44.7869, 13.4679, -31.5139),
            glm::vec3(-42.4073, 7.40826, -31.2008),
            glm::vec3(41.2799, 24.7468, -41.62),
            glm::vec3(35.7048, 18.3072, -48.2816),
            glm::vec3(41.1799, 14.3361, -44.8663),
            glm::vec3(44.9306, 13.3279, -47.8193),
            glm::vec3(46.8527, 29.5127, -47.1623),
            glm::vec3(43.038, 30.9073, -47.816),
            glm::vec3(43.253, 29.2816, -52.3075),
            glm::vec3(24.8474, 13.0081, 57.9246),
            glm::vec3(16.2656, 11.6615, 60.9399),
            glm::vec3(12.4625, 12.1914, 49.2405),
            glm::vec3(-1.67983, 10.386, 97.6237),
            glm::vec3(3.86908, 6.00625, 103.602),
            glm::vec3(-41.811, 12.8513, 16.7567),
            glm::vec3(-46.8636, 17.1877, 11.9196),
            glm::vec3(-45.731, 20.7948, 20.6651),
    };

    for(int i = 0; i < sizeof fireFlyPositions / sizeof fireFlyPositions[0]; i++) {
        std::shared_ptr<treeStruct> fire = std::make_shared<treeStruct>("fire" + std::to_string(i), std::move(std::make_unique<FireFly>(fireFlyPositions[i])), fireFlyPositions[i], glm::vec3 {0, 0, 0}, glm::vec3 {0.1, 0.1, 0.1});
        (dynamic_cast<FireFly*>(fire->obj.get()))->lightIndex = lightCount + i;
        (dynamic_cast<FireFly*>(fire->obj.get()))->isStatic =true;

        if(dynamic_cast<FireFly*>(fire->obj.get())->isStatic) {
            lights[lightCount].position = fireFlyPositions[i];
            lights[lightCount].color = Config::CONFIG_FIREFLY_COLOR;
            lights[lightCount].range = 13.0f;
            lights[lightCount++].strength = 3.0f;
        }
        sceneStructure->addChild(fire);
    }
}

void printSceneInitProgress(int progress, int max) {
    if (progress != 0) {
        std::cout << "\r";
    }
    std::cout << "Scene init progress: " << std::round(progress * 100.0 / max) << "%" << std::endl;
}

void Scene::generateWheatField(std::shared_ptr<treeStruct> fieldStruct) {
    std::cout << "Generating wheat field..." << std::endl;
    std::shared_ptr<treeStruct> field_ground = std::make_shared<treeStruct>("field_ground", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                      glm::vec3 {0, 3.7, 0}, glm::vec3 {3*ppgso::PI/2, 0, 0}, glm::vec3 {0.15,0.15,0.15});
    fieldStruct->addChild(field_ground);

    std::shared_ptr<treeStruct> scarecrow = std::make_shared<treeStruct>("scarecrow", std::move(std::make_unique<Scarecrow>()), glm::vec3 {0,9,0});
    fieldStruct->addChild(scarecrow);

    std::shared_ptr<treeStruct> ravenOnScarecrow1 = std::make_shared<treeStruct>("raven_on_scarecrow1", std::move(std::make_unique<JumpingRaven>()), glm::vec3 {0,0.6,0.6});
    scarecrow->addChild(ravenOnScarecrow1);

    std::shared_ptr<treeStruct> ravenOnScarecrow2 = std::make_shared<treeStruct>("raven_on_scarecrow2", std::move(std::make_unique<JumpingRaven>()), glm::vec3 {0,0.6,-0.4});
    scarecrow->addChild(ravenOnScarecrow2);

    int wheats = 0;
    glm::vec3 oldpos = {0,5.8,0};
    while (wheats < MAX_WHEATS) {
        glm::vec3 newpos = {Utils::randomNumber(2, 6), 0, Utils::randomNumber(2, 6)};
        newpos = oldpos + newpos;
        if (abs(newpos.x) <= 18 && abs(newpos.z) <= 18) {
            std::shared_ptr<treeStruct> wheat = std::make_shared<treeStruct>("wheat", std::move(std::make_unique<Wheat>()),
                                                                                 newpos, glm::vec3 {3*ppgso::PI/2,0,0}, glm::vec3 {0.07, 0.07, (float)Utils::randomInt(10,14)/100});
            fieldStruct->addChild(wheat);
            wheats++;
            oldpos = newpos;
            if (wheats % (MAX_WHEATS / 20) == 0) {
                std::cout << '*';
            }
        }
    }
    std::cout << std::endl;

}
