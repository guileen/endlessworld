#ifndef INSIGHT_INPUT_H
#define INSIGHT_INPUT_H

#include <iostream>
/*----------------------------------------------------------------
所有输入相关的代码
*/
namespace ins{

    float lastX = 0;
    float lastY = 0;
    bool firstMouse = true;
    Camera *camera;

    void initInput(GLFWwindow* window, Camera* camera);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
}

namespace ins{
    void initInput(GLFWwindow* window, Camera* _camera) {
        camera = _camera;
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        lastX = width/2.0f;
        lastY = height/2.0f;

        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // tell GLFW to capture our mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        std::cout << "xpos" << xpos << " ypos" << ypos << std::endl;
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera->ProcessMouseMovement(xoffset, yoffset);
    }

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        camera->ProcessMouseScroll(yoffset);
    }
}

#endif //INSIGHT_INPUT_H