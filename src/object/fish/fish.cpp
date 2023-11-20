#include "fish.h"
#include "shaders/texture_vert_glsl.h"
#include "shaders/texture_frag_glsl.h"
#include "src/utils/bezier/bezier.h"
#include "src/object/fish/fishSpawner.h"
#include "src/object/particles/bubble.h"
#include "src/utils/utils.h"
#include "src/object/cat/cat.h"

void createSplashParticles(glm::vec3 position, Scene &scene);

Fish::Fish(const std::string model, const std::string texture, ENUM_FISH_TYPE fishType) {
    if (!shader) {
        shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    }
    if (!this->texture) {
        this->texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(texture));
    }
    if (!mesh) {
        mesh = std::make_unique<ppgso::Mesh>(model);
    }
    this->fishType = fishType;
}

bool Fish::update(Scene &scene, float dt) {
    glm::vec3 futurePosition;

    currentTimeInPath += dt;

    if(fishType == ENUM_FISH_TYPE::BUCKET_FISH) {
        futurePosition = Bezier::bezierRec(BUCKET_FISH_PATH_POINTS, currentTimeInPath / FishSpawner::BUCKET_FISH_PATH_TIME_INTERVAL);
    } else if(fishType == ENUM_FISH_TYPE::WATER_FISH) {
        futurePosition = Bezier::bezierRec(LAKE_FISH_PATH_POINTS, currentTimeInPath / FishSpawner::LAKE_FISH_PATH_TIME_INTERVAL);
    }

    position = futurePosition;
    generateModelMatrix();

    if (position.y < -33.0) {
        createSplashParticles(position, scene);
        return false;
    }

    return true;
}

void Fish::render(Scene &scene) {
    auto camera = *scene.camera;

    shader->use();

    shader->setUniform("LightDirection", scene.LIGHT_DIRECTION);
    shader->setUniform("ProjectionMatrix", camera.projectionMatrix);
    shader->setUniform("ViewMatrix", camera.viewMatrix);
    shader->setUniform("CamPos", camera.position);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture, 0);

    mesh->render();
}

Fish::Fish(const std::string model, const std::string texture, glm::vec3 position, glm::vec3 rotation,
           Fish::ENUM_FISH_TYPE fishType) : Fish(model, texture, fishType) {
    this->position = position;
    this->rotation = rotation;

    if (fishType == ENUM_FISH_TYPE::WATER_FISH) {
        LAKE_FISH_PATH_POINTS.push_back(position);
        position.y += 2.0f;
        glm::vec3 point = Utils::getPointTowards(position, rotation.x, 5.0f);
        LAKE_FISH_PATH_POINTS.push_back(point);
        point.y -= 2.0f;
        LAKE_FISH_PATH_POINTS.push_back(Utils::getPointTowards(point, rotation.x, 4.0f));
    }

}

void createSplashParticles(glm::vec3 position, Scene &scene) {
    glm::vec3 bubblePosition = position;
    bubblePosition.y = -33;
    for (int i = 0, particles = Utils::randomInt(5, 15); i < particles; ++i) {
        double angle = i * (2 * M_PI / particles);
        bubblePosition.x += float(1.0f * cos(angle));
        bubblePosition.z += float(1.0f * sin(angle));

        auto bubble = std::make_unique<Bubble>(bubblePosition, glm::vec3{angle, 0, 0}, glm::vec3{0.25, 0.25, 0.25}, glm::vec3{0, 1, 0});
        scene.objects.push_back(move(bubble));

//        std::shared_ptr<treeStruct> tree = std::make_shared<treeStruct>("bubble", std::move(bubble));
//        scene.sceneStructure->addChild(tree);
    }
}