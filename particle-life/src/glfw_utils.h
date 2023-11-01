#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <iostream>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

const float positions[] = {
    -0.5f, -0.5f,
    -0.5f,  0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f
};

void game_loop(GLFWwindow* window)
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 2 * sizeof(positions) / sizeof(positions[0]));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    return;
}

GLFWwindow* glfw_setup() {
    assert(glfwInit());

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Particle Life", NULL, NULL);
    if (!window)
    {
        std::cerr << "window initialization failed" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "glew initialization failed!" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    return window;
}

