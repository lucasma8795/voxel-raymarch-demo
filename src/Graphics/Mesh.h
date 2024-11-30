#pragma once

#include "Graphics/Buffer.h"
#include "Graphics/BufferLayout.h"


namespace VoxelRaymarchDemo
{


// OpenGL Vertex Array.
// Mesh is not valid unless a VBO and an EBO are both set.
class Mesh
{
public:
    Mesh(std::unique_ptr<VertexBuffer>&& vbo,
         std::unique_ptr<IndexBuffer>&& ebo,
         const BufferLayout& vboLayout);
    ~Mesh();

    // Use this mesh.
    void bind() const;

    // Number of vertices in this mesh.
    std::size_t size() const;


private:
    RendererID rendererID;

    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<IndexBuffer> ebo;
};


}