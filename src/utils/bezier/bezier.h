//
// Created by wraith on 18.11.2023.
//

#ifndef PPGSO_BEZIER_H
#define PPGSO_BEZIER_H

#include "ppgso.h"

class Bezier {
public:
    static glm::vec3 bezierRec(std::vector<glm::vec3> points, float t);
    static glm::vec3 getPoint(glm::vec3 p1, glm::vec3 p2, float t);
};

#endif //PPGSO_BEZIER_H
