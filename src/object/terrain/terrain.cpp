#include "terrain.h"
#include "shaders/texture_frag_glsl.h"
#include <shaders/texture_vert_glsl.h>

Terrain::Terrain(const std::string model, const std::string texture) : Terrain(model) {
    if (!this->texture) {
        this->texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(texture));
    }
}

Terrain::Terrain(const std::string model) {
    position = {0, 0, 0};
    rotation = {0, 0, 0};
    scale = {1, 1, 1};

    if (!shader) {
        shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    }

    if (!mesh) {
        mesh = std::make_unique<ppgso::Mesh>(model);
    }
}

bool Terrain::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Terrain::render(Scene &scene) {
    auto camera = *scene.camera;

    shader->use();

    shader->setUniform("LightDirection", scene.LIGHT_DIRECTION);
    shader->setUniform("ProjectionMatrix", camera.projectionMatrix);
    shader->setUniform("ViewMatrix", camera.viewMatrix);
    shader->setUniform("CamPos", camera.position);

    shader->setUniform("ModelMatrix", modelMatrix);

    if (texture) {
        shader->setUniform("Texture", *texture, 0);
    }

    mesh->render();
}

