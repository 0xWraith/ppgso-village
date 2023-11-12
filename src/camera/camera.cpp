#include "camera.h"

Camera::Camera(float fow, float ratio, float near, float far) {
    projectionMatrix = recalculateProjectionMatrix(fow, ratio, near, far);
}

void Camera::update() {
    viewMatrix = glm::lookAt(
            position,
            position + cameraFront,
            cameraUp
            );
}

glm::mat4 Camera::recalculateProjectionMatrix(float fov, float ratio, float near, float far) {
    this->fov = fov;
    this->ratio = ratio;
    this->near = near;
    this->far = far;
    return glm::perspective(glm::radians(fov), ratio, near, far);
}

void Camera::moveTowards(const glm::vec3 &position, const glm::vec3 &rot, float speed) {

}


