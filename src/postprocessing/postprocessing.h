//
// Created by wraith on 12/2/2023.
//

#ifndef PPGSO_POSTPROCESSING_H
#define PPGSO_POSTPROCESSING_H

#include "ppgso.h"

class PostProcessing {
private:
    float noiseTime = 0;
    std::unique_ptr<ppgso::Shader> shaderBlur;
    std::unique_ptr<ppgso::Shader> shaderBloom;

    unsigned int hdrFBO;
    unsigned int colorBuffers[2];
    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];

    unsigned int quadVAO = 0;
    unsigned int quadVBO;

public:
    PostProcessing(int width, int height);
    void renderQuad();
    void render();
    void init();
};


#endif //PPGSO_POSTPROCESSING_H
