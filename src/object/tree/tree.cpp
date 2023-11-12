#include "tree.h"
#include <shaders/texture_frag_glsl.h>
#include <shaders/texture_vert_glsl.h>

Tree::Tree(const std::string model, const std::string texture) {
    position = {0, 0.75, 0};
    rotation = {3*ppgso::PI/2, 0, 0};
    scale = {0.5, 0.5, 0.5};

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

bool Tree::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Tree::render(Scene &scene) {
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

