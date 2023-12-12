#include "ppgso.h"
#include "src/scene/scene.h"
#include "src/postprocessing/postprocessing.h"
#include "shaders/framebuffer_frag_glsl.h"

#include "src/utils/config/config.h"

#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1440

bool Config::CONFIG_BLOOM = true;
bool Config::CONFIG_NOISE = true;
bool Config::DAY_TIME = true;

class VillageWindow : public ppgso::Window {
public:
    Scene scene;
    PostProcessing postProcessing{-1, -1};
private:
    float lastTime = 0;
    float deltaTime = 0;

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

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);

        lastTime = (float) glfwGetTime();
        postProcessing = PostProcessing(width, height);
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

        glEnable(GL_DEPTH_TEST);
        glClearColor(230 / 255.0, 230 / 255.0, 255 / 255.0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        postProcessing.init();
        scene.update(deltaTime);
        scene.render();
        postProcessing.render();
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
    while (villageWindow.pollEvents()) {
    }
    return EXIT_SUCCESS;
}

