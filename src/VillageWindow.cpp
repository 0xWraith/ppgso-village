#include <iostream>
#include "ppgso.h"
#include "src/scene/scene.h"

#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1440

void onScroll(GLFWwindow *window, double xoffset, double yoffset);
class VillageWindow : public ppgso::Window {
public:
    Scene scene;
private:
    float lastTime = 0;
    float deltaTime = 0;
    unsigned int BLOOM_FRAMEBUFFER_WIDTH = 1280;
    unsigned int BLOOM_FRAMEBUFFER_HEIGHT = 720;
    unsigned int fbo;

public:
    bool firstMouse = true;
    double lastX = 0.0;
    double lastY = 0.0;
    float yaw = -90.0f;
    float pitch = 0.0f;

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
//        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        lastTime = (float) glfwGetTime();
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
        glClearColor(230 / 255.0, 230 / 255.0, 255 / 255.0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.update(deltaTime);
        scene.render();
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

