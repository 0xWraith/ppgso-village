#include "House.h"
#include <shaders/texture_frag_glsl.h>
#include <shaders/texture_vert_glsl.h>

House::House(const std::string model, const std::string texture) {
    position = {0, 2.75, 0};
    rotation = {0, 0, 0};
    scale = {1, 1, 1};

    if (!shader) {
        shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    }
    if (!this->texture) {
        this->texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(texture));
    }
    if (!mesh) {
        mesh = std::make_unique<ppgso::Mesh>(model);
    }
}

bool House::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void House::render(Scene &scene) {
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

