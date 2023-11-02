//
// Created by wraith on 02.11.2023.
//

#ifndef PPGSO_OBJECT_H
#define PPGSO_OBJECT_H

#include <glm/glm.hpp>

class Scene;

class Object {
protected:
    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{1, 1, 1};
    glm::mat4 modelMatrix{1};
public:
    Object() = default;
    Object(const Object &) = default;
    Object(Object &&) = default;
    virtual ~Object() = default;

    virtual bool update(Scene &scene, float dt) = 0;
    virtual void render(Scene &scene) = 0;

    virtual void onClick(Scene &scene) {};

    glm::vec3 getPosition() const { return position; }
    glm::vec3 getRotation() const { return rotation; }
    glm::vec3 getScale() const { return scale; }
    glm::mat4 getModelMatrix() const { return modelMatrix; }
protected:
    void generateModelMatrix();
};

#endif //PPGSO_OBJECT_H
