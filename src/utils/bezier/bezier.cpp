#include "bezier.h"

glm::vec3 Bezier::bezierRec(std::vector<glm::vec3> points, float t) {
    if (points.size() == 2) {
        return getPoint(points.at(0), points.at(1), t);
    }
    std::vector<glm::vec3> newPoints;
    for (unsigned long long i = 0; i < points.size() - 1; i++) {
        newPoints.emplace_back(getPoint(points.at(i), points.at(i + 1), t));
    }
    return bezierRec(newPoints, t);
}

glm::vec3 Bezier::getPoint(glm::vec3 p1, glm::vec3 p2, float t) {
    glm::vec3 tmp = {
            p1.x - (p1.x - p2.x) * t,
            p1.y - (p1.y - p2.y) * t,
            p1.z - (p1.z - p2.z) * t
    };
    return tmp;
}