#include "dog.h"
#include "shaders/texture_vert_glsl.h"
#include "shaders/texture_frag_glsl.h"
#include "shaders/phong_frag_glsl.h"
#include "shaders/phong_vert_glsl.h"
#include "src/utils/bezier/bezier.h"

Dog::Dog(const std::string model, const std::string texture) {
    rotation = {3*ppgso::PI/2, 0, 0};
    scale = {1, 1, 1};

    if (!shader) {
        shader = std::make_unique<ppgso::Shader>(phong_vert_glsl, phong_frag_glsl);
    }
    if (!this->texture) {
        this->texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(texture));
    }
    if (!mesh) {
        mesh = std::make_unique<ppgso::Mesh>(model);
    }
    position = path_points.at(0);
}


bool Dog::update(Scene &scene, float dt) {

    currentTimeInPath += dt;

    glm::vec3 new_position = Bezier::bezierRec(path_points, currentTimeInPath / 60.0f);
    auto deltaPos = glm::normalize(position - new_position);
    position = new_position;

    rotation.y = float(atan2(deltaPos.x, deltaPos.z) + glm::radians(180.0));

    if (currentTimeInPath >= 60.0f) {
        currentTimeInPath = 0;
    }

    generateModelMatrix();
    return true;
}

void Dog::render(Scene &scene) {
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
