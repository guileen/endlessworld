#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/camera.h>
#include "model.h"
#include "mesh.h"
#include <iostream>
#include <map>

// 场景Scene 包含 摄像机、Models，Model包含 RenderOrder Meshs，Shaders，Mesh指明其所使用的Shader，通过一个Draw方法，自动渲染。
// 程序执行的过程是:
// 执行一些物理引擎的操作。更新models、摄像机，更新models需要使用哪个shader，以及渲染时所要设置的一些参数。
// 按一定的顺序应用每个shader，对每个shader绘制models。有些操作对顺序有要求，比如“描边”操作。
// Scene 需要尽可能的隐藏openGL的操作和关键字，达到平台无关性，将来亦可改造适配。


class Scene {
    public:
        Scene(GLFWwindow *window) {
            shader = new Shader("shaders/basic_lighting.vs", "shaders/basic_lighting.fs");
            camera = new Camera(glm::vec3(0, 0, 1));
            glfwGetWindowSize(window, &this->width, &this->height);
            Scene::windowMapToScene[window] = this;
            // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glfwSetCursorPosCallback(window, &Scene::processMouseCallback);
            // glfwSetScrollCallback(window, scroll_callback);
        }
        // 自动添加不存在的摄像机，默认有一个
        void setCamera(unsigned int cameraIndex, glm::vec3 position, glm::vec3 direction, glm::vec3 up);
        // camera的引用, 用于调整方向
        Camera& getCamera(unsigned int cameraIndex);
        // 鼠标旋转视角
        void processMouseRotate(double xpos, double ypos, unsigned int effectCameraIndex=0);

        // 向场景添加model（entity？？？）
        void addModel(const Model& model);

        void removeModel(const Model& model);

        // 增加光源
        void addDirLight();
        void addSpotLight();
        void addPointLight();

        // 向场景中添加网格
        void addMesh(const Mesh& mesh) {
            std::cout << "mesh" << mesh.vertices.size() << std::endl;
            meshes.push_back(mesh);
        }

        void render() {
            glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)width / (float)height, 0.1f, 100.0f);
            glm::mat4 view = camera->GetViewMatrix();
            shader->use();
            shader->setMat4("projection", projection);
            shader->setMat4("view", view);
            shader->setVec3("viewPos", camera->Position);
            shader->setMat4("model", glm::mat4(1.0f));

            // 平行光, 蓝色的月光
            shader->setVec3("dirLight.direction", glm::vec3(1.0,-1.0,-0.5));
            shader->setVec3("dirLight.ambient", 0.1,0.1,0.2);
            shader->setVec3("dirLight.diffuse", 0.2,0.2,0.4);
            shader->setVec3("dirLight.specular", 0.5,0.5,0.8);

            for(auto mesh: meshes) {
                mesh.Draw(*shader);
            }
        }

        // 设置默认shader
        void setDefaultShader();

        // 使用某shader渲染某model，默认的model应该有个shader，一个model可以被多个shader渲染，
        void bindShaderModel(Shader& shader, Model& model);

        void onMouseMove(double xpos, double ypos) {
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

        Camera* camera;
    private:
        vector<Mesh> meshes;
        Shader* shader;
        int width;
        int height;
        float lastX;
        float lastY;
        bool firstMouse = true;
        // 为了能够定位到具体callback对应关系
        static std::map<GLFWwindow*,Scene*> windowMapToScene;
        static void processMouseCallback(GLFWwindow* window, double xpos, double ypos) {
            auto scene = Scene::windowMapToScene[window];
            scene->onMouseMove(xpos, ypos);
        }
};

std::map<GLFWwindow*,Scene*> Scene::windowMapToScene = std::map<GLFWwindow*,Scene*>();
