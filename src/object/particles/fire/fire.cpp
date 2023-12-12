
//#include "fire.h"
#include "shaders/color_frag_glsl.h"
#include "shaders/color_vert_glsl.h"
#include "fire.h"
#include "src/utils/utils.h"
#include "src/utils/config/config.h"

Fire::Fire(glm::vec3 speed, int color, float lifetime) {
    this->speed = speed;
    if (color == 1) {
        this->color = Config::CONFIG_FIRE_PARTICLE_COLOR;
    }
    else if (color == 2) {
        this->color = Config::CONFIG_FIRE2_PARTICLE_COLOR;
    }
    else if (color == 3) {
        this->color = Config::CONFIG_FIRE3_PARTICLE_COLOR;
    }


    this->lifeTime = lifetime;
    if (!shader) {
        shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    }
    if (!mesh) {
        mesh = std::make_unique<ppgso::Mesh>("models/bubble.obj");
    }
}

bool Fire::update(Scene &scene, float dt) {

//    position.y += 0.5f;
//    position.x += (rand() % 2) - 0.5f;
//    position.z += (rand() % 2) - 0.5f;

//    speed = glm::vec3(Utils::randomInt(-6, 6), Utils::randomInt(1, 4), Utils::randomInt(-6, 6));
    lifeTime -= dt;
    position.x += speed.x * dt * 0.15f;
    position.y += speed.y * dt;
    position.z += speed.z * dt * 0.15f;

    position = position + glm::vec3 (0.65,0,0) * dt;
    //If life time is less than 0, remove particle
    if (lifeTime <= 0.0f) {
        return false;
    }

    generateModelMatrix();
    return true;
}

void Fire::render(Scene &scene) {
    auto camera = *scene.camera;
    shader->use();
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("ViewMatrix", camera.viewMatrix);
    shader->setUniform("ProjectionMatrix", camera.projectionMatrix);
    shader->setUniform("OverallColor", color);
    mesh->render();
}
