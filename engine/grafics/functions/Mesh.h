#include "inc_gr.h"

#pragma once

class Mesh
{
public:
unsigned int VAO, VBO, EBO;

    Mesh(float* vertices, size_t vSize, unsigned int* indices, size_t iSize);
    ~Mesh();
    void Draw();

private:
    size_t indexCount;

};

