#include <iostream>
#include "ppgso.h"
#include "src/scene/scene.h"
#include "shaders/framebuffer_frag_glsl.h"
#include "shaders/framebuffer_vert_glsl.h"
#include "shaders/pp_bloom_frag_glsl.h"
#include "shaders/pp_noise_frag_glsl.h"

#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1440

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
};

void onScroll(GLFWwindow *window, double xoffset, double yoffset);

class VillageWindow : public ppgso::Window {
public:
    Scene scene;
private:
    float lastTime = 0;
    float deltaTime = 0;
    float noiseTime = 0;
    unsigned int BLOOM_FRAMEBUFFER_WIDTH = 1280;
    unsigned int BLOOM_FRAMEBUFFER_HEIGHT = 720;
    unsigned int fbo;

public:
    bool firstMouse = true;
    double lastX = 0.0;
    double lastY = 0.0;
    float yaw = -90.0f;
    float pitch = 0.0f;
    unsigned int framebuffer;
    unsigned int textureColorbuffer;
    unsigned int quadVAO, quadVBO;
    unsigned int rectangleVAO;
    std::unique_ptr<ppgso::Shader> framebufferShader;
    std::unique_ptr<ppgso::Shader> noiseShader;


public:
    VillageWindow() : Window{"Dmytro Dzhuha | Marek Hužvár | Village", WINDOW_WIDTH, WINDOW_HEIGHT} {
        lastX = (double)width / 2.0f;
        lastY = (double)height / 2.0f;

        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetScrollCallback(window, onScroll);



        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);

        lastTime = (float) glfwGetTime();

        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glGenTextures(1, &textureColorbuffer);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOW_WIDTH, WINDOW_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        framebufferShader = std::make_unique<ppgso::Shader>(framebuffer_vert_glsl, framebuffer_frag_glsl);
        framebufferShader->use();
        framebufferShader->setUniform("screenTexture", 0);
        framebufferShader->setUniform("noiseTexture", 1);

        noiseShader = std::make_unique<ppgso::Shader>(framebuffer_vert_glsl, pp_noise_frag_glsl);
        noiseShader->use();
        noiseShader->setUniform("screenTexture", 0);

        scene.init();
    }

    void onKey(int key, int scancode, int action, int mods) override {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        scene.keyboard[key] = action;
    }

    void changeWindowSize(int width, int height) {
        glfwSetWindowSize(window, width, height);
        lastX = (float)width / 2.0f;
        lastY = (float)height / 2.0f;
    }

    void onIdle() override {
        deltaTime = (float) glfwGetTime() - lastTime;
        lastTime = (float) glfwGetTime();


        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        glClearColor(230 / 255.0, 230 / 255.0, 255 / 255.0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.update(deltaTime);
        scene.render();


        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);

        framebufferShader->use();
        noiseShader->use();
        noiseTime += 0.0001;
        noiseShader->setUniform("time", noiseTime);
        glBindVertexArray(quadVAO);
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void onCursorPos(double cursorX, double cursorY) override {
        Camera* camera = scene.camera.get();

        if (firstMouse) {
            lastX = cursorX;
            lastY = cursorY;
            firstMouse = false;
        }

        auto xoffset = float(cursorX - lastX);
        auto yoffset = float(lastY - cursorY);

        lastX = cursorX;
        lastY = cursorY;

        float sensitivity = 0.05f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f) {
            pitch = 89.0f;
        } else if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        glm::vec3 front;
        front.x = float(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
        front.y = float(sin(glm::radians(pitch)));
        front.z = float(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
        camera->cameraFront = glm::normalize(front);

        camera->update();
    }
};

VillageWindow villageWindow;

int main() {
//    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
//    villageWindow.changeWindowSize(mode->width, mode->height);
    while (villageWindow.pollEvents()) {

    }
    return EXIT_SUCCESS;
}

void onScroll(GLFWwindow* window, double xoffset, double yoffset) {
    Camera* camera = villageWindow.scene.camera.get();

    float newFow = camera->fov + (float) yoffset;

    if (newFow < 1) {
        newFow = 1;
    } else if (newFow > 179) {
        newFow = 179;
    }

    camera->projectionMatrix = camera->recalculateProjectionMatrix(
            newFow,
            camera->ratio,
            camera->near,
            camera->far
    );
}

