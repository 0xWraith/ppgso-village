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

void printSceneInitProgress(int progress, int max);

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

void Scene::update(float time) {
    auto i = std::begin(objects);
    while (i != std::end(objects)) {
        Object* obj = i->get();
        if (obj->update(*this, time)) {
            ++i;
        } else {
            i = objects.erase(i);
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
    if (keyboard[GLFW_KEY_0]) {
        std::cout << "Camera position: " << camera->position.x << ", " << camera->position.y << ", " << camera->position.z << std::endl;
    }
    if (keyboard[GLFW_KEY_9]) {

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
}

void Scene::render() {

    for (auto& obj: objects) {
        obj->render(*this);
    }

    if(sceneStructure) {
        sceneStructure->render(*this);
    }
}

void Scene::init() {
    int progress = 0;
    const int maxProgress = 26;

    generateSkybox();
    printSceneInitProgress(++progress, maxProgress);

    objects.clear();
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

    std::shared_ptr<treeStruct> house = std::make_shared<treeStruct>("house", std::move(std::make_unique<House>("models/house.obj", "textures/house.bmp")),
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

    std::shared_ptr<treeStruct> depthSand1 = std::make_shared<treeStruct>("depthSand1", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {0.0, -31.0, 133.0}, glm::vec3 {glm::radians(315.0), 0, 0}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand1);

    std::shared_ptr<treeStruct> depthSand2 = std::make_shared<treeStruct>("depthSand2", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {-100.0, -31.0, 140.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0.0, glm::radians(45.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand2);

    std::shared_ptr<treeStruct> depthSand3 = std::make_shared<treeStruct>("depthSand3", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {100.0, -31.0, 140.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0, glm::radians(-45.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand3);

    std::shared_ptr<treeStruct> depthSand4 = std::make_shared<treeStruct>("depthSand4", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {-145, -31.0, 245.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0, glm::radians(90.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand4);

    std::shared_ptr<treeStruct> depthSand5 = std::make_shared<treeStruct>("depthSand5", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {145, -31.0, 245.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0, glm::radians(-90.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand5);

    std::shared_ptr<treeStruct> depthSand6 = std::make_shared<treeStruct>("depthSand6", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {-100, -31.0, 350.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0.0, glm::radians(135.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand6);

    std::shared_ptr<treeStruct> depthSand7 = std::make_shared<treeStruct>("depthSand7", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {100, -31.0, 350.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0, glm::radians(-135.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand7);

    std::shared_ptr<treeStruct> depthSand8 = std::make_shared<treeStruct>("depthSand8", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/sand.bmp")),
                                                                          glm::vec3 {0.0, -31.0, 390.5 + 21.0}, glm::vec3 {glm::radians(315.0), 0, glm::radians(180.0)}, glm::vec3 {0.5, 0.3, 0.5});
    sceneStructure->addChild(depthSand8);

    std::shared_ptr<treeStruct> water = std::make_shared<treeStruct>("water", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/water.bmp")),
                                                                     glm::vec3 {0.0, -45, 250}, glm::vec3 {3*ppgso::PI/2, 0, 0}, glm::vec3 {1, 1, 1});
    //Cast to Terrain
    ((Terrain*)water->obj.get())->type = Terrain::TERRAIN_TYPE::WATER;
    sceneStructure->addChild(water);

    std::shared_ptr<treeStruct> dog = std::make_shared<treeStruct>("dog", std::move(std::make_unique<Dog>("models/dog.obj", "textures/dog.bmp")),
                                                                   glm::vec3 {-20, 10, 0}, glm::vec3 {glm::radians(270.0), 0, 0}, glm::vec3 {0.1, 0.1, 0.1});
    sceneStructure->addChild(dog);

    std::shared_ptr<treeStruct> bucket = std::make_shared<treeStruct>("bucket", std::move(std::make_unique<Bucket>("models/bucket.obj", "textures/bucket.bmp")),
                                                                      glm::vec3 {0.0, 4.2, 101.0},
                                                                      glm::vec3 {glm::radians(0.0), 0, 0},
                                                                      glm::vec3 {0.25, 0.25, 0.25});
    sceneStructure->addChild(bucket);

    std::shared_ptr<treeStruct> waterInBucket1 = std::make_shared<treeStruct>("waterInBucket1", std::move(std::make_unique<Terrain>("models/grass.obj", "textures/water.bmp")),
                                                                              glm::vec3 {0.0, 5.0, 101.0},
                                                                              glm::vec3 {3*ppgso::PI/2, 0, 0},
                                                                              glm::vec3 {0.005, 0.005, 0.005});
//    ((Terrain*)waterInBucket1->obj.get())->type = Terrain::TERRAIN_TYPE::WATER;
    sceneStructure->addChild(waterInBucket1);

    /*std::shared_ptr<treeStruct> fish1 = std::make_shared<treeStruct>("fish1", std::move(std::make_unique<Fish>("models/fish1.obj", "textures/fish1.bmp")),
                                                                     glm::vec3 {5.0, 5.0, 101.0},
                                                                     glm::vec3 {glm::radians(0.0), 0, 0},
                                                                     glm::vec3 {0.5, 0.5, 0.5});
    sceneStructure->addChild(fish1);

    std::shared_ptr<treeStruct> fish2 = std::make_shared<treeStruct>("fish2", std::move(std::make_unique<Fish>("models/fish2.obj", "textures/fish2.bmp")),
                                                                     glm::vec3 {10.0, 5.0, 101.0},
                                                                     glm::vec3 {glm::radians(270.0), glm::radians(90.0), 0},
                                                                     glm::vec3 {0.1, 0.1, 0.1});
    sceneStructure->addChild(fish2);


    std::shared_ptr<treeStruct> fish3 = std::make_shared<treeStruct>("fish3", std::move(std::make_unique<Fish>("models/fish3.obj", "textures/fish3.bmp")),
                                                                     glm::vec3 {15.0, 5.0, 101.0},
                                                                     glm::vec3 {glm::radians(0.0), 0, 0},
                                                                     glm::vec3 {0.5, 0.5, 0.5});
    sceneStructure->addChild(fish3);*/



    /*
    for(int i = 0; i < 0; i++) {
        auto gate_first_row = std::make_unique<Terrain>("models/gate.obj", "textures/gate.bmp");
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
        printSceneInitProgress(++progress, maxProgress);
    }
    */

    std::cout << "Scene init done" << std::endl;
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

    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(skyBoxTextures[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            std::cout << "Loaded texture: " << skyBoxTextures[i] << std::endl;
            std::cout << "Width: " << width << std::endl;
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D
                    (
                            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                            0,
                            GL_RGB,
                            width,
                            height,
                            0,
                            GL_RGB,
                            GL_UNSIGNED_BYTE,
                            data
                    );
            stbi_image_free(data);
        }
        else
        {
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

void printSceneInitProgress(int progress, int max) {
    if (progress != 0) {
        std::cout << "\r";
    }
    std::cout << "Scene init progress: " << std::round(progress * 100.0 / max) << "%%" << std::endl;
}
