#include "scene.h"
#include <shaders/skybox_vert_glsl.h>
#include <shaders/skybox_frag_glsl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "src/object/bucket/bucket.h"
#include "src/object/cat/cat.h"
#include "src/object/dog/dog.h"
#include "src/object/fish/fish.h"
#include "src/object/garden/garden.h"
#include "src/object/grandma/grandma.h"
#include "src/object/grandpa/grandpa.h"
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
#include "src/object/spiderman/spiderman.h"
#include "src/object/raven/raven.h"
#include "src/object/raven/wingedRaven.h"


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

        std::shared_ptr<treeStruct> fire = std::make_shared<treeStruct>("fire_" + std::to_string(Utils::randomInt(1, 1000)), std::move(std::make_unique<Fire>(glm::vec3(Utils::randomInt(-2, 2), Utils::randomInt(1, 4), Utils::randomInt(-2, 2)),glm::vec3 {1.0f, 0.0f, 0.0f})),
                                                                        glm::vec3  {-43.5,5.7,35.5}, glm::vec3 {0, 0, 0}, glm::vec3 {0.05, 0.15, 0.05});
        sceneStructure->addChild(fire);
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
    const int maxProgress = 38;

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

    std::shared_ptr<treeStruct> spiderman = std::make_shared<treeStruct>("spiderman", std::move(std::make_unique<Spiderman>()),
                                                                         glm::vec3 {-10, 4.2, 101.0},
                                                                         glm::vec3 {0, 0, 0},
                                                                         glm::vec3 {2, 2, 2});
    sceneStructure->addChild(spiderman);
    printSceneInitProgress(++progress, maxProgress);

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
        /*auto gate_first_row = std::make_unique<Terrain>("models/gate.obj", "textures/gate.bmp");
        gate_first_row->rotation = {3 * ppgso::PI / 2, 0, 0};
        gate_first_row->scale = {0.1, 0.1, 0.1};
        gate_first_row->position = {-58.0 + (i * 27.6), 3.5, -70.0};
        objects.push_back(std::move(gate_first_row));
        printSceneInitProgress(++progress, maxProgress);

        auto gate_third_row = std::make_unique<Terrain>("models/gate.obj", "textures/gate.bmp");
        gate_third_row->rotation = {3 * ppgso::PI / 2, 0.0, ppgso::PI / 2};
        gate_third_row->scale = {0.1, 0.1, 0.1};
        gate_third_row->position = {-72, 3.5, -56.0 + (i * 27.6)};
        objects.push_back(std::move(gate_third_row));
        printSceneInitProgress(++progress, maxProgress);

        auto gate_fourth_row = std::make_unique<Terrain>("models/gate.obj", "textures/gate.bmp");
        gate_fourth_row->rotation = {3 * ppgso::PI / 2, 0.0, ppgso::PI / 2};
        gate_fourth_row->scale = {0.1, 0.1, 0.1};
        gate_fourth_row->position = {66, 3.5, -56.0 + (i * 27.6)};
        objects.push_back(std::move(gate_fourth_row));
        printSceneInitProgress(++progress, maxProgress);*/

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



    std::shared_ptr<treeStruct> pickaxe = std::make_shared<treeStruct>("pickaxe", std::move(std::make_unique<Pickaxe>()));
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
        lights[lightCount].color = {200 / 255.0, 200 / 255.0, 200 / 255.0};
        lights[lightCount].range = 5000.0f;
        lights[lightCount++].strength = 5.f;
        return;
    }

    lights[lightCount].position = {666.655, 1654.05, 967.464};
    lights[lightCount].color = {29 / 255.0, 78 / 255.0, 105 / 255.0};
    lights[lightCount].range = 5000.0f;
    lights[lightCount++].strength = 3.5f;

    lights[lightCount].position = glm::vec3(633.615, 1729.08, 979.094);
    lights[lightCount].color = {255 / 255.0, 255 / 255.0, 255 / 255.0};
    lights[lightCount].range = 300.0f;
    lights[lightCount++].strength = 10.5f;

    glm::vec3 gasLampPositions[] = {
            glm::vec3(-35.0, 5, -30.0),
            glm::vec3(-50.0, 5, -30.0),
            glm::vec3(-3.62255, 3, 99.046),
            glm::vec3(37.3796, 5.10996, -46.4953)
    };

    for(int i = 0; i < sizeof gasLampPositions / sizeof gasLampPositions[0]; i++) {

        lights[lightCount].position = gasLampPositions[i];
        lights[lightCount].position.y += 2.5;
        lights[lightCount].color = {255 / 255.0, 136 / 255.0, 49 / 255.0};
        lights[lightCount].range = 40.0f;
        lights[lightCount++].strength = 10.0f;

        std::shared_ptr<treeStruct> gaslamp = std::make_shared<treeStruct>("gaslamp" + std::to_string(i), std::move(std::make_unique<Terrain>("models/lamp.obj", "textures/lamp.bmp")),gasLampPositions[i], glm::vec3 {0, 0, 0}, glm::vec3 {0.5, 0.5, 0.5});
        sceneStructure->addChild(gaslamp);

        std::shared_ptr<treeStruct> gaslampLight = std::make_shared<treeStruct>("gaslamplight" + std::to_string(i), std::move(std::make_unique<GasLampLight>(lights[2 + i].color)),glm::vec3 {0, 2.5, 0}, glm::vec3 {0, 0, 0}, glm::vec3 {2, 2, 2});
        sceneStructure->addObject("gaslamp" + std::to_string(i), gaslampLight);
    }

    glm::vec3 fireFlyPositions[] = {
            glm::vec3(46.6131, 23.2622, -38.1185),
            glm::vec3(40.0278, 22.3502, -38.5949),
            glm::vec3(39.7968, 22.2931, -38.6928),
            glm::vec3(38.8064, 21.1217, -42.1043),
            glm::vec3(35.5501, 19.5796, -45.8631),
            glm::vec3(43.8664, 19.525, -63.9955),
            glm::vec3(46.4989, 21.7079, -59.6947),
            glm::vec3(46.0526, 22.7108, -58.9834),
            glm::vec3(37.5285, 24.9817, -59.6726),
            glm::vec3(39.2137, 28.0762, -62.2611),
            glm::vec3(41.9187, 29.9846, -60.9166),

            glm::vec3(-101.372, -27.1368, 237.037),
            glm::vec3(-93.9439, -17.6613, 224.629),
            glm::vec3(-83.2368, -27.1901, 226.492),
            glm::vec3(-61.312, -16.4515, 251.158),
            glm::vec3(-60.2665, -27.4105, 251.804),
            glm::vec3(-59.1748, -27.3677, 252.479),
            glm::vec3(-58.0832, -16.3249, 253.154),
            glm::vec3(-56.9888, -16.282, 253.831),
            glm::vec3(-55.8971, -27.2393, 254.506),
            glm::vec3(-54.802, -16.1964, 255.183),
            glm::vec3(-53.7097, -16.1535, 255.859),
            glm::vec3(-52.6153, -27.1107, 256.536),
            glm::vec3(-20.4753, -14.8512, 276.41),
            glm::vec3(-19.9281, -27.8298, 276.749),
            glm::vec3(-19.4933, -27.8128, 277.018),
            glm::vec3(-9.32532, -14.4143, 283.306),
            glm::vec3(-8.99865, -27.4015, 283.508),
            glm::vec3(20.9712, -13.2272, 302.04),
            glm::vec3(22.0477, -27.185, 302.706),
            glm::vec3(22.8127, -27.155, 303.179),
            glm::vec3(67.18, -10.9095, 283.887),
            glm::vec3(68.5153, -278247, 281.722),
            glm::vec3(69.19, -27.7819, 280.628),
            glm::vec3(70.5403, -276962, 278.439),
            glm::vec3(71.2137, -27.6534, 277.348),
            glm::vec3(72.5648, -27.5677, 275.157),
            glm::vec3(73.2399, -27.5248, 274.063),
            glm::vec3(57.5986, -10.4049, 196.843),
            glm::vec3(56.9437, -10.4306, 196.438),
            glm::vec3(43.9334, -10.9404, 188.392),
            glm::vec3(25.3499, -27.6686, 176.9),
            glm::vec3(24.9139, -27.6857, 176.631),
            glm::vec3(0.0962955, -27.226, 181.458),
            glm::vec3(-7.0364, -27.4081, 180.586),
            glm::vec3(-6.31377, -27.578, 175.897),
            glm::vec3(-4.00426, -27.4647, 177.558),
            glm::vec3(-8.06937, -27.2988, 183.9),
            glm::vec3(-8.02754, -27.2948, 183.979),
            glm::vec3(-7.98487, -27.2907, 184.06),
            glm::vec3(-4.91746, -27.2746, 182.859),
            glm::vec3(-5.90925, -27.4081, 179.994),
            glm::vec3(-6.75353, -27.7605, 178.386),
            glm::vec3(-2.80792, -27.4881, 176.314),
            glm::vec3(-1.90866, -27.2089, 182.922),
            glm::vec3(-10.4591, -27.3262, 184.436),
            glm::vec3(-11.8527, -27.4598, 181.781),

            glm::vec3(64.8318, -1.04672, 130.064),
            glm::vec3(72.6345, -2.02778, 125.175),
            glm::vec3(68.5839, -0.372302, 136.645),
            glm::vec3(134.931, -7.29579, 188.775),
            glm::vec3(141.895, -7.60678, 194.786),
            glm::vec3(141.913, -7.61072, 194.876),
            glm::vec3(141.931, -7.61456, 194.964),
            glm::vec3(131.736, -10.9071, 275.519),
            glm::vec3(131.754, -10.911, 275.609),
            glm::vec3(131.772, -10.9149, 275.697),
            glm::vec3(135.469, -12.1782, 305.071),
            glm::vec3(135.038, -12.1823, 305.255),
            glm::vec3(134.97, -12.186, 305.357),
            glm::vec3(80.9053, -14.5308, 341.09),
            glm::vec3(74.3916, -13.5109, 397.251),
            glm::vec3(74.3134, -13.508, 397.299),
            glm::vec3(42.628, -12.5656, 403.051),
            glm::vec3(41.8781, -12.5485, 402.873),
            glm::vec3(-52.8058, -9.82799, 409.59),
            glm::vec3(-105.776, -9.39869, 361.143),
            glm::vec3(-138.269, -10.4575, 319.241),
            glm::vec3(-139.03, -10.5018, 318.745),
            glm::vec3(-143.532, -11.1432, 311.133),
            glm::vec3(-146.894, -15.3821, 259.127),
            glm::vec3(-140.995, -15.2907, 258.745),
            glm::vec3(-140.088, -14.382, 258.687),
            glm::vec3(-148.526, -5.37918, 259.232),
            glm::vec3(-98.6259, -16.9193, 177.776),
            glm::vec3(-68.5357, 0.0523268, 127.224),

            glm::vec3(11.415, 16.7821, 84.2328),
            glm::vec3(9.19195, 15.9767, 90.5971),
            glm::vec3(-3.96336, 16.0197, 82.5852),
            glm::vec3(4.01537, 10.2094, 106.075),
            glm::vec3(-4.9488, 8.60827, 106.892),
            glm::vec3(-8.57837, 7.44412, 101.931),
            glm::vec3(-8.48173, 6.93985, 94.578),

            glm::vec3(-37.2311, 22.8469, -38.3259),
            glm::vec3(-45.459, 20.0522, -36.2535),
            glm::vec3(-42.7281, 19.2702, -31.5347),
            glm::vec3(-31.9688, 11.1009, 2.94698),
            glm::vec3(-32.0678, 7.0697, -13.0689),
            glm::vec3(-30.4551, 13.31, -20.7007),
            glm::vec3(-36.3614, 11.2214, 10.4418),
            glm::vec3(-43.6273, 11.3555, 11.5963),
            glm::vec3(-42.9232, 10.4165, 18.592),
            glm::vec3(-40.8161, 16.5325, 9.24365),
            glm::vec3(-55.7486, 6.60205, 2.9977),
            glm::vec3(-55.7167, 6.61554, 2.91269),
            glm::vec3(-55.6852, 6.62888, 2.82864),
            glm::vec3(-55.6539, 6.64214, 2.74501),
            glm::vec3(-55.5907, 6.66888, 2.57648),
            glm::vec3(-55.5611, 6.6814, 2.49756),
            glm::vec3(-56.6015, 8.51297, -11.0591),
            glm::vec3(46.7538, 30.7801, -52.0289),

            glm::vec3(-39.6879, 10.8675, -34.27),
            glm::vec3(-43.6781, 14.1054, -31.9131),
            glm::vec3(-50.5999, 8.54739, -39.7979),
            glm::vec3(-42.9395, 6.16821, -44.1019),
            glm::vec3(-39.7291, 6.31674, -62.358),
            glm::vec3(-34.3271, 20.912, -11.4463),
            glm::vec3(-30.6248, 18.4365, 6.51366),
            glm::vec3(-42.3183, 18.7172, -37.256),
            glm::vec3(-34.0737, 18.6167, -34.6102),
            glm::vec3(-34.8092, 19.9527, -27.4604),
            glm::vec3(-49.7454, 23.7035, 3.93544),
            glm::vec3(-49.5068, 21.9461, -5.1445),
            glm::vec3(-52.5883, 19.916, -15.7219),
            glm::vec3(-50.2468, 20.3854, -23.4163),
            glm::vec3(-47.3091, 22.9038, -23.2454),
            glm::vec3(-45.9627, 25.5516, -18.656),
            glm::vec3(44.8513, 26.4914, -53.8175),
            glm::vec3(47.3662, 30.166, -52.1148),
            glm::vec3(42.7897, 29.238, -51.8878),
            glm::vec3(40.619, 38.2182, -54.7615),
            glm::vec3(40.6952, 45.0715, -55.0801),
            glm::vec3(41.2903, 46.9094, -48.9851),
            glm::vec3(41.6894, 44.8252, -49.6387),
            glm::vec3(40.7353, 53.0714, -50.0645),
            glm::vec3(39.3084, 52.2244, -49.3574),
            glm::vec3(37.0179, 50.5272, -49.3477),
            glm::vec3(-42.4085, 6.34924, -34.3486),
            glm::vec3(-45.8553, 10.7848, -32.6264),
            glm::vec3(-40.9255, 11.0233, -31.4153),
            glm::vec3(-38.0525, 12.9353, -31.4485),
            glm::vec3(49.9253, 30.1915, -52.5548),
            glm::vec3(47.9984, 29.212, -48.2217),
            glm::vec3(53.2145, 30.8534, -47.8745),
            glm::vec3(51.662, 31.6459, -50.4929),
    };

    for(int i = 0; i < sizeof fireFlyPositions / sizeof fireFlyPositions[0]; i++) {
        std::shared_ptr<treeStruct> fire = std::make_shared<treeStruct>("fire" + std::to_string(i), std::move(std::make_unique<FireFly>(fireFlyPositions[i])), fireFlyPositions[i], glm::vec3 {0, 0, 0}, glm::vec3 {0.1, 0.1, 0.1});
        (dynamic_cast<FireFly*>(fire->obj.get()))->lightIndex = 6 + i;
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
    std::cout << "Scene init progress: " << std::round(progress * 100.0 / max) << "%%" << std::endl;
}

void Scene::generateWheatField(std::shared_ptr<treeStruct> fieldStruct) {
    std::cout << "Generating wheat field..." << std::endl;
    std::shared_ptr<treeStruct> field_ground = std::make_shared<treeStruct>("field_ground", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                      glm::vec3 {0, 3.7, 0}, glm::vec3 {3*ppgso::PI/2, 0, 0}, glm::vec3 {0.15,0.15,0.15});
    fieldStruct->addChild(field_ground);

    std::shared_ptr<treeStruct> scarecrow = std::make_shared<treeStruct>("scarecrow", std::move(std::make_unique<Scarecrow>()), glm::vec3 {0,9,0});
    fieldStruct->addChild(scarecrow);

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
