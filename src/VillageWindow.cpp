#include <iostream>
#include "ppgso.h"

class VillageWindow : public ppgso::Window {
private:

public:
    VillageWindow() : Window{"Dmytro Dzhuha | Marek Hužvár | Village", 1, 1} {
        hideCursor();
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
    }

    void changeWindowSize(int width, int height) {
        glfwSetWindowSize(window, width, height);
    }

    void onIdle() override {

    }

    GLFWwindow *getWindow() {
        return window;
    }
};

int main() {
    VillageWindow window;
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window.changeWindowSize(mode->width, mode->height);
    while (window.pollEvents()) {

    }
    return EXIT_SUCCESS;
}
