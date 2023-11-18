#include "utils.h"

glm::vec3 Utils::getPointTowards(glm::vec3 position, float angle, float distance) {
    return glm::vec3(position.x + distance * cos(angle), position.y, position.z + distance * sin(angle));
}

int Utils::randomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}
