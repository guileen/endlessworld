#pragma once
/**
 * 生成几何图形
 */

#include <vector>
#include "mesh.h"

using namespace std;

// 球 参考：
// https://schneide.blog/2016/07/15/generating-an-icosphere-in-c/
// https://github.com/libigl/eigen/blob/master/demos/opengl/icosphere.cpp
// http://www.songho.ca/opengl/gl_sphere.html
// https://en.wikipedia.org/wiki/Geodesic_polyhedron
 
namespace icosahedron
{
    const float X=.525731112119133606f;
    const float Z=.850650808352039932f;
    const float N=0.f;
    
    static const vector<glm::vec3> vertices=
    {
        {-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
        {N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
        {Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
    };
    
    static const vector<glm::ivec3> triangles=
    {
        {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
        {8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
        {7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
        {6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
    };
}

Mesh createIcoSphere(int level) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    for(auto vertexPosition: icosahedron::vertices) {
        Vertex v;
        v.Position = glm::vec3(vertexPosition[0], vertexPosition[1], vertexPosition[2]);
        v.Normal = v.Position;
        vertices.push_back(v);
    }

    for(auto index: icosahedron::triangles) {
        indices.push_back(index[0]);
        indices.push_back(index[1]);
        indices.push_back(index[2]);
    }
    return Mesh(vertices, indices, textures);
}

Mesh createTriangleModel(vector<glm::vec3> points, glm::vec4 color) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    glm::vec3 normal = (points[1] - points[0])*(points[2]-points[1]);
    for(auto position: points) {
        Vertex v;
        v.Position = position;
        v.Normal = normal;
        vertices.push_back(v);
    }
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    return Mesh(vertices, indices, textures);
}

Mesh createCubeModel();
