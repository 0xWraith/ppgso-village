#ifndef PPGSO_CINEMATIC_H
#define PPGSO_CINEMATIC_H

#include "vector"
#include "keyframe.h"

class Scene;

class Cinematic {
private:
    bool started = false;
    std::vector<Keyframe> keyframes;
    Keyframe currentKeyframe;
    int currentKeyframeIndex = -1;
public:
    Cinematic();
    void addKeyframe(Keyframe keyframe);
    void start(Scene &scene);
    void update(Scene &scene, float dt);
    bool isStarted();
    void stop();

    ~Cinematic() = default;

private:
    void selectKeyframe(int index);
};

#endif
