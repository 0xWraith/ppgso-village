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
}

void Scene::render() {
    for (auto& obj: objects) {
        obj->render(*this);
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

    auto grass = std::make_unique<Terrain>("models/grass.obj", "textures/water.bmp");
    grass->rotation = {3*ppgso::PI/2, 0, 0};
    grass->scale = {0.5, 0.5, 0.5};
    objects.push_back(std::move(grass));
    printSceneInitProgress(++progress, maxProgress);

    for(int i = 0; i < 5; i++) {
        auto gate_first_row = std::make_unique<Terrain>("models/gate.obj", "textures/gate.bmp");
        gate_first_row->rotation = {3 * ppgso::PI / 2, 0, 0};
        gate_first_row->scale = {0.1, 0.1, 0.1};
        gate_first_row->position = {-58.0 + (i * 27.6), 3.5, -70.0};
        objects.push_back(std::move(gate_first_row));
        printSceneInitProgress(++progress, maxProgress);

        auto gate_second_row = std::make_unique<Terrain>("models/gate.obj", "textures/gate.bmp");
        gate_second_row->rotation = {3 * ppgso::PI / 2, 0, 0};
        gate_second_row->scale = {0.1, 0.1, 0.1};
        gate_second_row->position = {-58.0 + (i * 27.6), 3.5, 68.5};
        objects.push_back(std::move(gate_second_row));
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

    auto house = std::make_unique<House>("models/house.obj", "textures/house.bmp");
    house->rotation = {0, 0, 0};
    house->position = {-43.1071, 3.80, -20.6743};
    objects.push_back(std::move(house));
    printSceneInitProgress(++progress, maxProgress);

    auto dog = std::make_unique<Dog>("models/dog.obj", "textures/dog.bmp");
    dog->position = {-20, 10, 0};
    dog->scale = {0.1, 0.1, 0.1};
    objects.push_back(std::move(dog));
    printSceneInitProgress(++progress, maxProgress);


    auto cat = std::make_unique<Cat>("models/cat.obj", "textures/cat.bmp");
    cat->position = {-15, 10, 0};
    objects.push_back(std::move(cat));
    printSceneInitProgress(++progress, maxProgress);


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
