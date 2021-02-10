#pragma once
#include <insight/mesh.h>

class Model {
    public:
        Model(Mesh mesh):mesh(mesh){

        }
        Mesh mesh;    
    private:
};