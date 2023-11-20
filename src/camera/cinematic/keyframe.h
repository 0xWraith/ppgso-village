#ifndef PPGSO_KEYFRAME_H
#define PPGSO_KEYFRAME_H

#include "ppgso.h"

class Keyframe {
public:
    enum ENUM_KEYFRAME_TYPE {
        STATIC,
        DYNAMIC
    };
    ENUM_KEYFRAME_TYPE KEYFRAME_TYPE = DYNAMIC;
    float KEYFRAME_TIME = 0.0f;
    float KEYFRAME_TIME_INTERVAL = 0.0f;

    glm::vec3 KEYFRAME_START_LOOK_AT;
    glm::vec3 KEYFRAME_START_POSITION;

    glm::vec3 KEYFRAME_DESTINATION_LOOK_AT;
    glm::vec3 KEYFRAME_DESTINATION_POSITION;

    Keyframe() = default;
};

#endif
