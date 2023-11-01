#include "glfw_utils.h"

int WinMain(void)
{
    GLFWwindow* window = glfw_setup();
    assert(window != nullptr);

    game_loop(window);

    glfwTerminate();

    return 0;
}

