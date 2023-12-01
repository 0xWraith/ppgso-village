//
// Created by wraith on 12/1/2023.
//

#include "fireflies.h"
#include "src/utils/utils.h"
#include "shaders/color_frag_glsl.h"
#include "shaders/color_vert_glsl.h"

FireFly::FireFly(glm::vec3 position) {
    glm::vec3 pos = glm::vec3(
            position.x + float(Utils::randomInt(-3, 3)),
            position.y + float(Utils::randomInt(-3, 3)),
            position.z + float(Utils::randomInt(-3, 3)));

    this->position = pos;
    if(!shader) {
        shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    }
    if(!mesh) {
        mesh = std::make_unique<ppgso::Mesh>("models/bubble.obj");
    }
}

bool FireFly::update(Scene &scene, float dt) {

    lifeTime += dt;
//    if (lifeTime > 2.0f) {
//        speed = glm::vec3(
//                float(Utils::randomInt(-3, 3)),
//                float(Utils::randomInt(-3, 3)),
//                float(Utils::randomInt(-3, 3)));
//        lifeTime = 0.0f;
//    }

    if (isStatic && lifeTime > 0.5f) {
        speed = glm::vec3(
                float(Utils::randomInt(-1, 1)),
                float(Utils::randomInt(-1, 1)),
                float(Utils::randomInt(-1, 1)));
        lifeTime = 0.0f;
    }
    if (!isStatic && lifeTime > 2.0f) {
        speed = glm::vec3(
                float(Utils::randomInt(-3, 3)),
                float(Utils::randomInt(-1, 1)),
                float(Utils::randomInt(-3, 3)));
        lifeTime = 0.0f;
    }

    position += speed * dt;

    if (position.y >= 30.0f) {
        position.y = 30.0f;
        speed.y = -speed.y;
    }

    if (lightIndex != -1) {
        scene.lights[lightIndex].position = position;
    }

    generateModelMatrix();
    return true;
}

void FireFly::render(Scene &scene) {
    auto camera = *scene.camera;
    shader->use();
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("ViewMatrix", camera.viewMatrix);
    shader->setUniform("ProjectionMatrix", camera.projectionMatrix);
    shader->setUniform("OverallColor", color);
    mesh->render();
}
