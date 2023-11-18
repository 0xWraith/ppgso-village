//
// Created by wraith on 18.11.2023.
//

#ifndef PPGSO_UTILS_H
#define PPGSO_UTILS_H

#include "ppgso.h"

class Utils {
public:
    static glm::vec3 getPointTowards(glm::vec3 position, float angle, float distance);
    static int randomInt(int min, int max);
};


#endif //PPGSO_UTILS_H
