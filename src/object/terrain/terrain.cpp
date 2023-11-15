#include "terrain.h"
#include "shaders/texture_frag_glsl.h"
#include <shaders/texture_vert_glsl.h>

#include <cmath>

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

    if (type == WATER) {
        animationTime += dt;

        if (animationTime > 1000 * M_PI) {
            animationTime = 0;
        }

        auto waterLevel = -45.0f + std::sin(animationTime) * 2.0f;
        auto waterRotation = std::sin(animationTime) * 0.1f;
        position.y = waterLevel;
        rotation.z = glm::radians(waterRotation);
    }

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

