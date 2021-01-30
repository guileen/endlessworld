#ifndef IMMERSION_ASSETS_H
#define IMMERSION_ASSETS_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <stb_image.h>
#include <filesystem>
#include <iostream>

namespace ins
{
    enum
    {
        default_channels = 0, // only used for desired_channels
        grey = 1,
        greya = 2,
        rgb = 3,
        rgba = 4
    };
    int loadImage(const char *path);
    int load3DModel(const char *path);
    // 加载材质
    int loadTexture(const char *path, unsigned int *texture, int req_channels);
    int uniformTexture(int shaderId, const char *glVariableName, int glTextureID, int texture);

}; // namespace imm

namespace ins
{
    int loadTexture(const char *path, unsigned int* texture, int req)
    {
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载并生成纹理
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(std::filesystem::path(path).c_str(), &width, &height, &nrChannels, req);
        if (data)
        {
            int glFlag = req == STBI_rgb_alpha ? GL_RGBA: GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, glFlag, width, height, 0, glFlag, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
            return 1;
        }
        stbi_image_free(data);
        return 0;
    }

    int uniformTexture(int shaderId, const char *glVariableName, int glTextureID, int texture) {
        if (glTextureID < GL_TEXTURE0 || glTextureID > GL_TEXTURE31) {
            std::cout << "uniformTexture: Invalid glTextureID" << glTextureID << std::endl;
            return 1;
        }
        int location = glTextureID - GL_TEXTURE0;
        glUniform1i(glGetUniformLocation(shaderId, glVariableName), location);
        glActiveTexture(glTextureID);
        glBindTexture(GL_TEXTURE_2D, texture);
        return 0;
    }
} // namespace immersion
#endif