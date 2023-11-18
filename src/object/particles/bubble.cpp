//
// Created by wraith on 18.11.2023.
//

#include "bubble.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>
#include "src/utils/utils.h"
#include "src/utils/bezier/bezier.h"

bool Bubble::update(Scene &scene, float dt) {
    lifeTime += dt;
//    position += speed * dt;

    glm::vec3 futurePosition = Bezier::bezierRec(BUBBLE_PATH_POINTS, lifeTime / 0.5);
    auto deltaPos = glm::normalize(position - futurePosition);
    position = futurePosition;

    if (lifeTime >= 0.5f) {
        return false;
    }

    generateModelMatrix();
    return true;
}

void Bubble::render(Scene &scene) {
    auto camera = *scene.camera;
    shader->use();
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("ViewMatrix", camera.viewMatrix);
    shader->setUniform("ProjectionMatrix", camera.projectionMatrix);
    shader->setUniform("OverallColor", color);
    mesh->render();
}

Bubble::Bubble(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 speed) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->speed = speed;
    this->color = glm::vec3(3 / 255.0f, 169 / 255.0f, 252 / 255.0f);

    if (!shader) {
        shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    }
    if (!mesh) {
        mesh = std::make_unique<ppgso::Mesh>("models/bubble.obj");
    }

    BUBBLE_PATH_POINTS.push_back(position);
    position.y += 1.0f;
    BUBBLE_PATH_POINTS.push_back(Utils::getPointTowards(position, rotation.x, 3.0f));
    position.y -= 2.0f;
    BUBBLE_PATH_POINTS.push_back(Utils::getPointTowards(position, rotation.x, 3.0f));
}
