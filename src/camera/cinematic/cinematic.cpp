#include "cinematic.h"

Cinematic::Cinematic() {
    this->keyframes = std::vector<Keyframe>();
}

void Cinematic::addKeyframe(Keyframe keyframe) {
    this->keyframes.push_back(keyframe);
}

void Cinematic::start() {

}
