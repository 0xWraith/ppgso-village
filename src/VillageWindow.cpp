#include <iostream>
#include "ppgso.h"
#include "src/scene/scene.h"

#include <shaders/skybox_vert_glsl.h>
#include <shaders/skybox_frag_glsl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1440

void onScroll(GLFWwindow *window, double xoffset, double yoffset);

float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
};

class VillageWindow : public ppgso::Window {
public:
    Scene scene;
private:
    float lastTime = 0;
    float deltaTime = 0;
    unsigned int BLOOM_FRAMEBUFFER_WIDTH = 1280;
    unsigned int BLOOM_FRAMEBUFFER_HEIGHT = 720;
    unsigned int fbo;
    std::unique_ptr<ppgso::Shader> skyboxShader;
    unsigned int cubemapTexture;

public:
    bool firstMouse = true;
    double lastX = 0.0;
    double lastY = 0.0;
    float yaw = -90.0f;
    float pitch = 0.0f;

    unsigned int skyboxVAO, skyboxVBO;
    unsigned int cubeVAO, cubeVBO;

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

        // cube VAO
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glBindVertexArray(cubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));


        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        std::string skyBoxTextures[6] = {
                "textures/skybox/graycloud_lf.jpg",
                "textures/skybox/graycloud_rt.jpg",
                "textures/skybox/graycloud_up.jpg",
                "textures/skybox/graycloud_dn.jpg",
                "textures/skybox/graycloud_ft.jpg",
                "textures/skybox/graycloud_bk.jpg"
        };


        glGenTextures(1, &cubemapTexture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

        for (unsigned int i = 0; i < 6; i++)
        {
            int width, height, nrChannels;
            unsigned char* data = stbi_load(skyBoxTextures[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                std::cout << "Loaded texture: " << skyBoxTextures[i] << std::endl;
                std::cout << "Width: " << width << std::endl;
                stbi_set_flip_vertically_on_load(false);
                glTexImage2D
                        (
                                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                0,
                                GL_RGB,
                                width,
                                height,
                                0,
                                GL_RGB,
                                GL_UNSIGNED_BYTE,
                                data
                        );
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Failed to load texture: " << skyBoxTextures[i] << std::endl;
                stbi_image_free(data);
            }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        skyboxShader = std::make_unique<ppgso::Shader>(skybox_vert_glsl, skybox_frag_glsl);
        skyboxShader->use();
//        skyboxShader->setUniform("skybox", 0);
        glUniform1i(glGetUniformLocation(skyboxShader->program, "skybox"), 0);

        glEnable(GL_DEPTH_TEST);

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



        glDepthFunc(GL_LEQUAL);

        skyboxShader->use();
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        view = glm::mat4(glm::mat3(scene.camera->viewMatrix));
//        glUniformMatrix4fv(glGetUniformLocation(skyboxShader->program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader->program, "projection"), 1, GL_FALSE, glm::value_ptr(scene.camera->projectionMatrix));
        glUniform3fv(glGetUniformLocation(skyboxShader->program, "model"), 1, glm::value_ptr(glm::mat4(1.0f)));

        skyboxShader->setUniform("view", view);
//        skyboxShader->setUniform("projection", projection);


        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);


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

