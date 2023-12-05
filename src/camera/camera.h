#ifndef PPGSO_CAMERA_H
#define PPGSO_CAMERA_H

#include <glm/glm.hpp>
#include "ppgso.h"
#include "src/camera/cinematic/cinematic.h"

class Camera {
private:

public:
    enum ENUM_CAMERA_MODE {
        FREE,
        CINEMATIC
    };
    ENUM_CAMERA_MODE CAMERA_MODE = FREE;
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 CAMERA_LOOK_AT = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 position{-10, 5, 0};

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    float fov = 90.0f, ratio = 1.0f, near = 0.0001f, far = 10000.0f;

    Camera(float fov = 90.0f, float ratio = 1.0, float near = 0.1f, float far = 1000.0f);

    glm::mat4 recalculateProjectionMatrix(float fow, float ratio, float near, float far);

    void update();
    void moveTowards(const glm::vec3 &position, const glm::vec3 &rot, float speed);
};
#endif
