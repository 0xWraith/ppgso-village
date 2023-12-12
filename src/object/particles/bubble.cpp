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

    if (lifeTime >= 2.5f) {
        return false;
    }

    glm::vec3 gravity = glm::vec3{0,-9.8,0};
    glm::vec3 wind = glm::vec3{5,0,0};
    speed += ( (gravity) * dt);
    speed += ( (wind) * dt);
    position += speed * dt;

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

}
