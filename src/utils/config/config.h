//
// Created by wraith on 12/1/2023.
//

#ifndef PPGSO_CONFIG_H
#define PPGSO_CONFIG_H


#include "ppgso.h"

class Config {
public:
    static bool DAY_TIME;
    static bool CONFIG_BLOOM;
    static bool CONFIG_NOISE;
    constexpr static const glm::vec3 CONFIG_FIRE_PARTICLE_COLOR = glm::vec3(255 / 255.0f, 116 / 255.0f, 46 / 255.0f);
    constexpr static const glm::vec3 CONFIG_FIRE2_PARTICLE_COLOR = glm::vec3(255 / 255.0f, 229 / 255.0f, 168 / 255.0f);
    constexpr static const glm::vec3 CONFIG_FIRE3_PARTICLE_COLOR = glm::vec3(255 / 255.0f, 33 / 255.0f, 25 / 255.0f);
    constexpr static const glm::vec3 CONFIG_FIREFLY_COLOR = glm::vec3(44 / 255.0, 168 / 255.0, 158 / 255.0);
    constexpr static const glm::vec3 CONFIG_GAS_COLOR = glm::vec3(237 / 255.0, 126 / 255.0, 47 / 255.0);
};
#endif //PPGSO_CONFIG_H
