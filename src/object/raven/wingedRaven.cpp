//
// Created by marek on 12. 12. 2023.
//

#include "wingedRaven.h"
#include <shaders/phong_frag_glsl.h>
#include <shaders/phong_vert_glsl.h>

WingedRaven::WingedRaven() {
    position = {0, Utils::randomInt(40,48), 0};
    rotation = {0, 0, 0};
    scale = {0.5, 0.5, 0.5};

    if (!shader) {
        shader = std::make_unique<ppgso::Shader>(phong_vert_glsl, phong_frag_glsl);
    }
    if (!this->texture) {
        this->texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("textures/raven.bmp"));
    }
    if (!mesh) {
        mesh = std::make_unique<ppgso::Mesh>("models/wingedRaven.obj");
    }
}

bool WingedRaven::update(Scene &scene, float dt) {
    animationTime -= dt;
    if(animationTime <= 0) {
        speed = glm::vec3(
                float(Utils::randomInt(-5, 5)),
                0,
                float(Utils::randomInt(-5, 5)));

        if (position.x > 100) {
            speed.x *= -4;
        }
        if (position.x < -100) {
            speed.x = 4;
        }
        if (position.z > 100) {
            speed.z = -4;
        }
        if (position.z < -100) {
            speed.z = 4;
        }

        glm::vec3 vec1 = glm::normalize(glm::vec3 {0,0,1});
        glm::vec3 vec2 = glm::normalize(speed);

        float dotProduct = glm::dot(vec1, vec2);
        dotProduct = glm::clamp(dotProduct, -1.0f, 1.0f);
        float angle = glm::acos(dotProduct);

        if (speed.x <= 0) {
            angle *= -1;
        }

        animationTime = (float) Utils::randomInt(12,35) / 10.f;
        rotation = glm::vec3 (0, 0, angle);

    }

    position = position + (speed * dt);

    if (jumping) {
        float high = (float)sin(glfwGetTime()) * 1.7;
        if(high > 0) {
            position.y = high + 5;
        }
        else {
            position.y = 5;
            jumping = false;
        }
    }

    generateModelMatrix();

    return true;
}

void WingedRaven::render(Scene &scene) {
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
