#ifndef PPGSO_CAMERA_H
#define PPGSO_CAMERA_H

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>

class Camera {
private:

public:

    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 position{-10, 5, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 lookAt{0, 0, 0};

    glm::vec3 startPosition{0, 0, 0};
    glm::vec3 startPositionLookAt{0, 0, 0};

    glm::vec3 destinationPosition{0, 0, 0};
    glm::vec3 destinationPositionLookAt{0, 0, 0};

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    float fov = 90.0f, ratio = 1.0f, near = 0.0001f, far = 10000.0f;

    explicit Camera(float fov = 90.0f, float ratio = 1.0f, float near = 0.0001f, float far = 10000.0f);

    glm::mat4 recalculateProjectionMatrix(float fow, float ratio, float near, float far);

    void update();
    void moveTowards(const glm::vec3 &position, const glm::vec3 &rot, float speed);
};
#endif
