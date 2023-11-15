#include "glfw_utils.h"

int main(void)
{
    GLFWwindow* window = glfw_setup();
    ASSERT(window != nullptr);

    game_loop(window);

    glfwTerminate();

    return 0;
}

