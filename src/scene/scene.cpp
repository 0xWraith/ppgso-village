#include "scene.h"
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
    this->camera->update();
}

void Scene::render() {
    for (auto& obj: objects) {
        obj->render(*this);
    }
}

void Scene::init() {
    int progress = 0;
    const int maxProgress = 5;

    objects.clear();
    printSceneInitProgress(++progress, maxProgress);

    this->camera = std::make_unique<Camera>();
    printSceneInitProgress(++progress, maxProgress);

    auto grass = std::make_unique<Terrain>("models/grass.obj", "textures/grass.bmp");
    grass->rotation = {3*ppgso::PI/2, 0, 0};
    objects.push_back(std::move(grass));
    printSceneInitProgress(++progress, maxProgress);

    auto mountain = std::make_unique<Terrain>("models/MountainTerrain.obj", "textures/mountain1.bmp");
    objects.push_back(std::move(mountain));
    printSceneInitProgress(++progress, maxProgress);

    auto house = std::make_unique<House>("models/house.obj", "textures/house.bmp");
    objects.push_back(std::move(house));
    printSceneInitProgress(++progress, maxProgress);

    auto cat = std::make_unique<Cat>("models/cat.obj", "textures/cat.bmp");
    objects.push_back(std::move(cat));
    printSceneInitProgress(++progress, maxProgress);

    auto dog = std::make_unique<Dog>("models/dog.obj", "textures/dog.bmp");
    objects.push_back(std::move(dog));
    printSceneInitProgress(++progress, maxProgress);

    std::cout << "Scene init done" << std::endl;
}

void printSceneInitProgress(int progress, int max) {
    if (progress != 0) {
        std::cout << "\r";
    }
    std::cout << "Scene init progress: " << std::round(progress * 100.0 / max) << "%" << std::endl;
}
