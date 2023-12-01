//
// Created by wraith on 11/30/2023.
//

#include "gaslamplight.h"
#include "shaders/color_vert_glsl.h"
#include "shaders/color_frag_glsl.h"

GasLampLight::GasLampLight(glm::vec3 color) {
    this->color = color;
    if (!mesh) {
        mesh = std::make_unique<ppgso::Mesh>("models/bubble.obj");
    }
    if (!shader) {
        shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    }
}

bool GasLampLight::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void GasLampLight::render(Scene &scene) {
    shader->use();
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("OverallColor", color);
    mesh->render();
}
