#ifndef PPGSO_DOG_H
#define PPGSO_DOG_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Dog final : public Object {
public:
    std::unique_ptr<ppgso::Texture> shadow_map;
    std::vector<glm::vec3> path_points = {
            glm::vec3(52.1295, 6.10582, -36.9465),
            glm::vec3(59.3459, 7.124, -52.014),
            glm::vec3(48.4336, 5.31875, -59.5425),
            glm::vec3(28.2278, 6.36077, -58.1654),
            glm::vec3(31.1781, 5.43746, -41.5671),
            glm::vec3(15.1101, 5.1584, -30.1536),
            glm::vec3(-2.05142, 4.8532, -25.5037),
            glm::vec3(-21.8518, 4.94025, -22.6708),
            glm::vec3(-28.2359, 4.89786, -5.60246),
            glm::vec3(-26.7134, 4.7678, 7.66776),
            glm::vec3(-29.2781, 5.58834, 13.9999),
            glm::vec3(-39.1824, 6.33416, 13.5427),
            glm::vec3(-54.397, 5.36464, 13.7027),
            glm::vec3(-62.4007, 5.59456, 11.0846),
            glm::vec3(-63.7126, 6.26676, 39.3755),
            glm::vec3(-42.9481, 4.59454, 75.8072),
            glm::vec3(-22.7718, 4.27631, 91.8056),
            glm::vec3(-5.85102, 3.93628, 97.0198),
            glm::vec3(17.5311, 4.43216, 94.4571),
            glm::vec3(40.4445, 4.96303, 91.4692),
            glm::vec3(41.7278, 5.49756, 78.7052),
            glm::vec3(40.4117, 6.08724, 64.6457),
            glm::vec3(37.62, 6.36469, 58.0477),
            glm::vec3(37.5067, 6.96958, 43.6157),
            glm::vec3(28.3882, 7.63317, 24.7832),
            glm::vec3(15.1153, 7.03265, 23.6147),
            glm::vec3(0.751693, 5.05301, 22.5481),
            glm::vec3(10.8065, 5.00537, 4.16138),
            glm::vec3(22.6174, 6.59346, -14.9144),
            glm::vec3(30.5523, 4.56689, -29.4777),
            glm::vec3(41.5436, 4.95638, -34.0996),
            glm::vec3(47.1616, 4.93797, -31.7392),
    };
    float currentTimeInPath = 0.0f;
public:
    Dog(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};
#endif
