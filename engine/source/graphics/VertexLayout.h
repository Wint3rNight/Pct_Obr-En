#pragma once
#include <GL/glew.h>
#include <vector>
#include <stdint.h>

namespace ene
{
    struct VertexElement
    {
        GLuint index;//attribute index in shader
        GLuint size; //number of components
        GLuint type;//data type
        uint32_t offset;//offset in bytes from the start of the vertex
    };
    struct VertexLayout
    {
        std::vector<VertexElement> elements;//list of vertex attributes
        uint32_t stride = 0; //total size of a vertex in bytes
    };
}