#include "dog.h"
#include "shaders/texture_vert_glsl.h"
#include "shaders/texture_frag_glsl.h"

glm::vec3 getPoint(glm::vec3 p1, glm::vec3 p2, float t) {
    glm::vec3 tmp = {
            p1.x - (p1.x - p2.x) * t,
            p1.y - (p1.y - p2.y) * t,
            p1.z - (p1.z - p2.z) * t
    };
    return tmp;
}

glm::vec3 random_vec3(float mini, float maxi) {
    return {((float) rand() / (float) RAND_MAX) * (maxi - mini) + mini,
            ((float) rand() / (float) RAND_MAX) * (maxi - mini) + mini,
            ((float) rand() / (float) RAND_MAX) * (maxi - mini) + mini};
}

glm::vec3 bezierRec(std::vector<glm::vec3> points, float t) {

    if (points.size() == 2) {
        return getPoint(points.at(0), points.at(1), t);
    }

    std::vector<glm::vec3> new_points;

    for (int i = 0; i < points.size() - 1; i++) {
        new_points.emplace_back(getPoint(points.at(i), points.at(i + 1), t));
    }

    return bezierRec(new_points, t);
}

Dog::Dog(const std::string model, const std::string texture) {
    rotation = {3*ppgso::PI/2, 0, 0};
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
    position = path_points.at(0);
}

glm::vec3 offset = random_vec3(-0.3, 0.3);

bool Dog::update(Scene &scene, float dt) {

    currentTimeInPath += dt;

    glm::vec3 new_position = bezierRec(path_points, currentTimeInPath / 7);

    auto deltaPos = glm::normalize(position - (new_position + offset));
    position = new_position + offset;

    rotation.y = float(atan2(deltaPos.x, deltaPos.z) + glm::radians(180.0));

    if (currentTimeInPath >= 7.0f) {
        currentTimeInPath = 0;
    }

    generateModelMatrix();
    return true;
}

void Dog::render(Scene &scene) {
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
