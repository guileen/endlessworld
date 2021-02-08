#ifndef LEARNOPENGL_MODEL_H
#define LEARNOPENGL_MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <learnopengl/mesh.h>
#include <learnopengl/shader_m.h>

#include <string>
#include <fstream>
#include <vector>

#define aiToGlmVec3(v) glm::vec3(v.x, v.y, v.z)
#define aiToGlmVec2(v) glm::vec2(v.x, v.y)

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model {
    public:
        vector<Texture> textures_loaded;
        vector<Mesh> meshes;
        string directory;
        bool gammaCorrection;

        Model(string const &path, bool gamma = false) : gammaCorrection(gamma) {
            loadModel(path);
        }
        void Draw(Shader shader) {
            for(unsigned int i = 0; i < meshes.size(); i++) {
                meshes[i].Draw(shader);
            }
        }
    private:
        void processNode(aiNode *node, const aiScene *scene) {
            // 处理节点所有的网格
            for(unsigned int i = 0; i < node->mNumMeshes; i++) {
                aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
                meshes.push_back(processMesh(mesh, scene));
            }
            // 对子节点重复这一过程
            for(unsigned int i = 0; i < node->mNumChildren; i++) {
                processNode(node->mChildren[i], scene);
            }
        }
        Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
            vector<Vertex> vertices;
            vector<unsigned int> indices;
            vector<Texture> textures;

            for(unsigned int i=0;i<mesh->mNumVertices; ++i) {
                Vertex vertex;
                // 处理顶点位置，法线，纹理坐标
                vertex.Position = aiToGlmVec3(mesh->mVertices[i]);
                vertex.Normal = aiToGlmVec3(mesh->mNormals[i]);
                // 是否有纹理坐标
                if(mesh->mTextureCoords[0]) {
                    vertex.TexCoords = aiToGlmVec2(mesh->mTextureCoords[0][i]);
                }
                vertices.push_back(vertex);
            }
            // 处理索引
            for(unsigned int i=0;i<mesh->mNumFaces; ++i) {
                aiFace face = mesh->mFaces[i];
                for(unsigned int j = 0; j < face.mNumIndices; ++j) {
                    indices.push_back(face.mIndices[j]);
                }
            }
            // 处理材质
            if(mesh->mMaterialIndex >= 0) {
                aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
                vector<Texture> diffuseMaps = loadMaterialTextures(material,
                    aiTextureType_DIFFUSE, "texture_diffuse");
                std::cout<<"texture_diffuse map count:"<<diffuseMaps.size()<<std::endl;
                textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
                vector<Texture> specularMaps = loadMaterialTextures(material,
                    aiTextureType_SPECULAR, "texture_specualr");
                std::cout<<"texture_specular map count:"<<specularMaps.size()<<std::endl;
                textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            }
            return Mesh(vertices, indices, textures);
        }

        vector<Texture> loadMaterialTextures(aiMaterial *mat,
            aiTextureType type, string typeName) {
            vector<Texture> textures;
            for(unsigned int i=0;i < mat->GetTextureCount(type);++i) {
                aiString str;
                mat->GetTexture(type, i, &str);
                bool skip = false;
                for(unsigned int j = 0; j < textures_loaded.size(); ++j) {
                    if(std::strcmp(textures_loaded[j].path.c_str(), str.C_Str()) == 0) {
                        textures.push_back(textures_loaded[j]);
                        skip = true;
                        break;
                    }
                }
                if(!skip) {
                    Texture texture;
                    texture.id = TextureFromFile(str.C_Str(), directory);
                    texture.type = typeName;
                    texture.path = std::string(str.C_Str());
                    textures.push_back(texture);
                }
            }
            return textures;
        }

       void loadModel(string const &path) {
            Assimp::Importer importer;
            const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
                cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
                return;
            }
            directory = path.substr(0, path.find_last_of('/'));
            processNode(scene->mRootNode, scene);
        } 
};

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma) {
    string filename = string(path);
    filename = directory + '/' + filename;
    unsigned int textureId;
    glGenTextures(1, &textureId);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if(data) {
        GLenum format;
        if(nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    return textureId;
}

#endif