#ifndef PPGSO_OBJECT_H
#define PPGSO_OBJECT_H

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>

class Scene;

class Object {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 modelMatrix;
    std::unique_ptr<ppgso::Mesh> mesh;
    std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<ppgso::Texture> texture;
public:
    Object() = default;
    Object(const Object &) = default;
    Object(Object &&) = default;
    virtual ~Object() = default;

    virtual bool update(Scene &scene, float dt) = 0;
    virtual void render(Scene &scene) = 0;

protected:
    void generateModelMatrix();
};

#endif //PPGSO_OBJECT_H
