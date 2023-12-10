#include "cat.h"
#include "shaders/texture_vert_glsl.h"
#include "shaders/texture_frag_glsl.h"
#include "shaders/phong_frag_glsl.h"
#include "shaders/phong_vert_glsl.h"
#include <glm/gtc/random.hpp>



Cat::Cat(const std::string model, const std::string texture) {
    position = {-11.8634, 2.17891, 14.3175};
    rotation = {3*ppgso::PI/2, 0, 0};
    scale = {0.1, 0.1, 0.1};

    if (!shader) {
        shader = std::make_unique<ppgso::Shader>(phong_vert_glsl, phong_frag_glsl);
    }
    if (!this->texture) {
        this->texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(texture));
    }
    if (!mesh) {
        mesh = std::make_unique<ppgso::Mesh>(model);
    }
}

bool Cat::update(Scene &scene, float dt) {
    std::cout << "CAT ON X:" << this->position.x << " Y:" << this->position.y << " Z:" << this->position.z << std::endl;

    float speed = 0.8f;
    animationTime += dt;

    switch (animationStep) {
        case 0: {
            if (animationTime > 1.0f) {
                rotation.x = glm::radians(225.0);
                position.y += (speed - 0.2f) * dt;
            }
            if (animationTime >= 6) {
                animationStep = 1;
                animationTime = 0;
            }
            position.x += std::cos(rotation.y) * speed * dt;
            position.z += std::sin(rotation.y) * speed * dt;
            break;
        }
        case 1: {
            if (rotation.z <= glm::radians(-90.0)) {
                animationStep = 2;
                animationTime = 0;
            }
            else {
                if (rotation.x < glm::radians(315.0)) {
                    rotation.x += glm::radians(225.0 * dt * 1);
                }
                rotation.z -= glm::radians(90.0 * dt * 5);
            }
            break;
        }
        case 2: {
            if (animationTime > 4.0f) {
                rotation.x = glm::radians(295.0);
                position.y -= (speed - 0.5f) * dt;
            } else {
                position.y -= (speed - 0.2f) * dt;
            }

            if (animationTime >= 7) {
                animationStep = 3;
                animationTime = 0;
            }

            position.x -= std::cos(rotation.y) * speed * dt;
            position.z -= std::sin(rotation.y) * speed * dt;
            break;
        }
        case 3: {
            //position = {45.5, 25.5, -49.7439};
            rotation.x = glm::radians(245.0);
            rotation.z = glm::radians(90.0);
            animationStep = 4;
            animationTime = -0.5f;
            break;
        }
        case 4: {
            if (animationTime >= 7) {
                animationStep = 0;
                animationTime = -0.5f;
            }
        }
    }

    generateModelMatrix();
    return true;
}

void Cat::render(Scene &scene) {
    auto camera = *scene.camera;

    shader->use();

    shader->setUniform("global_lighting_on", false);
    shader->setUniform("LightDirection", scene.LIGHT_DIRECTION);
    shader->setUniform("ProjectionMatrix", camera.projectionMatrix);
    shader->setUniform("ViewMatrix", camera.viewMatrix);
    shader->setUniform("CamPos", camera.position);

    shader->setUniform("ModelMatrix", modelMatrix);



    shader->setUniform("material.ambient", {0.19125f, 0.0735f, 0.0225f});
    shader->setUniform("material.diffuse", {0.1, 0.1, 0.1});
    shader->setUniform("material.specular", {0.0, 0.0, 0.0});
    shader->setUniform("material.shininess", 10.0f);

    shader->setUniform("lights.count", scene.lightCount);

    for(int i = 0; i < scene.lightCount; i++) {
        shader->setUniform("lights.positions[" + std::to_string(i) + "]", scene.lights[i].position);
        shader->setUniform("lights.colors[" + std::to_string(i) + "]", scene.lights[i].color);
        shader->setUniform("lights.ranges[" + std::to_string(i) + "]", scene.lights[i].range);
        shader->setUniform("lights.strengths[" + std::to_string(i) + "]", scene.lights[i].strength);
    }


    if (texture) {
        shader->setUniform("Texture", *texture, 0);
    }

    mesh->render();
}
