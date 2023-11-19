//
// Created by wraith on 18.11.2023.
//

#ifndef PPGSO_CINEMATIC_H
#define PPGSO_CINEMATIC_H

#include "vector"
#include "keyframe.h"

class Cinematic {
private:
    std::vector<Keyframe> keyframes;
public:
    Cinematic();
    void addKeyframe(Keyframe keyframe);
    void start();
};

#endif //PPGSO_CINEMATIC_H
