/**
 * GLToy 图形学相关的一些小玩具。像积木一样的使用
 */

#ifndef GLTOY_H
#define GLTOY_H
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <insight/geometry.h>

#include <iostream>

// 初始化OpenGL窗口
GLFWwindow* gltoyCreateWindow(int width, int height) {
    if(!glfwInit()) {
        std::cout << "Fail to init gflw" << std::endl;
        return NULL;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Fail to create window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    return window;
}

#endif