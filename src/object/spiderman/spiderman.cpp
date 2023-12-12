//
// Created by marek on 12. 12. 2023.
//

#include "spiderman.h"
#include <shaders/phong_frag_glsl.h>
#include <shaders/phong_vert_glsl.h>


#include <shaders/texture_frag_glsl.h>
#include <shaders/texture_vert_glsl.h>

Spiderman::Spiderman() {
    position = {10, 10, 0};
    rotation = {0, 0, 0};
    scale = {1, 1, 1};

    if (!shader) {
        shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    }
    if (!this->texture) {
        this->texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("textures/spiderman.bmp"));
    }
    if (!mesh) {
        mesh = std::make_unique<ppgso::Mesh>("models/spiderman.obj");
    }
}

bool Spiderman::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Spiderman::render(Scene &scene) {
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

