#include "cinematic.h"

#include "src/object/fish/fish.h"
#include "src/utils/utils.h"

Cinematic::Cinematic() {
    this->keyframes = std::vector<Keyframe>();
}

void Cinematic::addKeyframe(Keyframe keyframe) {
    this->keyframes.push_back(keyframe);
}

void Cinematic::start(Scene &scene) {
    this->started = true;
    selectKeyframe(0);
    scene.camera->CAMERA_MODE = Camera::ENUM_CAMERA_MODE::CINEMATIC;

    scene.camera->position = this->currentKeyframe.KEYFRAME_START_POSITION;
    scene.camera->CAMERA_LOOK_AT = this->currentKeyframe.KEYFRAME_START_LOOK_AT;
}

bool Cinematic::isStarted() {
    return this->started;
}

void Cinematic::update(Scene &scene, float dt) {
    if (!this->isStarted() || this->currentKeyframeIndex == -1) {
        return;
    }
    if (currentKeyframe.KEYFRAME_TIME <= currentKeyframe.KEYFRAME_TIME_INTERVAL) {
        currentKeyframe.KEYFRAME_TIME += dt;
        float progress = currentKeyframe.KEYFRAME_TIME / currentKeyframe.KEYFRAME_TIME_INTERVAL;
        scene.camera->position = glm::lerp(currentKeyframe.KEYFRAME_START_POSITION,currentKeyframe.KEYFRAME_DESTINATION_POSITION, progress);
        scene.camera->CAMERA_LOOK_AT = glm::lerp(currentKeyframe.KEYFRAME_START_LOOK_AT,currentKeyframe.KEYFRAME_DESTINATION_LOOK_AT, progress);
    } else {
        if (currentKeyframeIndex + 1 < keyframes.size()) {
            selectKeyframe(currentKeyframeIndex + 1);
        } else {
            scene.camera->CAMERA_MODE = Camera::ENUM_CAMERA_MODE::FREE;
            this->stop();
        }
    }
}

void Cinematic::selectKeyframe(int index) {
    this->currentKeyframeIndex = index;
    this->currentKeyframe = this->keyframes[index];
}

void Cinematic::stop() {
    this->started = false;
}
