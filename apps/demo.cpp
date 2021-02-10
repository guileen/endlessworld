#include <insight/gltoy.h>
#include <insight/scene.h>
#include <iostream>

void processInput(GLFWwindow *window, Scene* scene, float deltaTime);

int main() {
    auto window = gltoyCreateWindow(1200, 800);
    if(window==NULL) {
        std::cout << "Failed to create window" << std::endl;
        return -1;
    }
    Scene scene(window);
    // auto triangle = createTriangleModel({{-0.5,-0.5,0}, {0.5,-0.5,0}, {0.5,0.5,0}}, glm::vec4(1.0,0.5,0.2,1));
    // scene.addMesh(triangle);
    auto sphere = createIcoSphere(2);
    scene.addMesh(sphere);

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window, &scene, deltaTime);
        /* Render here */
        glClearColor(0.1,0.1,0.1,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        scene.render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window, Scene* scene, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    auto camera = scene->camera;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->Position += glm::vec3(0.0f, 1.0f, 0.0f);
}
