#include <external/glew/include/GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "Camera.h"
#include "Headers/Shader.h"
#include "Model.h"
#include "Enemy.h"

// Global variables
GLFWwindow* window;
int screenWidth = 800;
int screenHeight = 600;
Camera camera(glm::vec3(0.0f, 1.75f, 3.0f));
std::vector<Enemy> enemies;

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Game", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Set callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Configure OpenGL
    glEnable(GL_DEPTH_TEST);

    // Build and compile shaders
    Shader ourShader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    // Load models
    Model weaponModel("path/to/weapon.obj");
    Model enemyModel("path/to/enemy.obj");

    // Create enemies
    for (int i = 0; i < 5; ++i) {
        enemies.emplace_back(glm::vec3(i * 2.0f, 0.0f, -10.0f), &enemyModel);
    }

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        // Update
        for (auto& enemy : enemies) {
            enemy.update(camera.getPosition(), 0.01f);
        }

        // Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        // View/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // Render weapon
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, camera.getPosition() + camera.getFront() + glm::vec3(0.5f, -0.5f, 0.0f));
        ourShader.setMat4("model", model);
        weaponModel.Draw(ourShader);

        // Render enemies
        for (auto& enemy : enemies) {
            enemy.render(ourShader);
        }

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}

// Process all input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, 0.01f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, 0.01f);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, 0.01f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, 0.01f);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    camera.ProcessMouseMovement(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}
