#pragma once

#include "shader_utils.h"
#include "error_utils.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void game_loop(GLFWwindow* window) {
    const float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    unsigned int buffer;
    GLCall(glGenBuffers(1, &buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(shader));

    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT(location != -1);
    GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));

    float r = 0.0f;
    float increment = 0.05f;

    while (!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
        GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f) increment = -0.05f;
        if (r < 0.0f) increment =  0.05f;

        r += increment;

        GLCall(glfwSwapBuffers(window));

        GLCall(glfwPollEvents());
    }

    GLCall(glDeleteProgram(shader));

    return;
}

GLFWwindow* glfw_setup() {
    ASSERT(glfwInit());

    // GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    // const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    // glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Particle Life", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "window initialization failed" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "glew initialization failed!" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwSwapInterval(1);

    return window;
}

