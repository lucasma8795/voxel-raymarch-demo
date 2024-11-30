#include "Graphics/Mesh.h"

#include "Core/Logging.h"


namespace VoxelRaymarchDemo
{


Mesh::Mesh(std::unique_ptr<VertexBuffer>&& vbo,
           std::unique_ptr<IndexBuffer>&& ebo,
           const BufferLayout& vboLayout)
    : vbo{std::move(vbo)}, ebo{std::move(ebo)}
{
    // Generate vertex array object
    GL_CHECK(glGenVertexArrays(1, &rendererID));

    // Bind VAO and VBO
    GL_CHECK(glBindVertexArray(rendererID));
    this->vbo->bind();

    // Enable vertex arrays within VAO
    uint32_t index = 0;
    for (const auto& element: vboLayout)
    {
        GL_CHECK(glEnableVertexAttribArray(index));
        
        switch (element.type)
        {
            case AttribType::Float:
                GL_CHECK(glVertexAttribPointer(
                    index,
                    element.count,
                    attribTypeToOpenGLType(element.type),
                    element.normalized ? GL_TRUE : GL_FALSE,
                    vboLayout.getStride(),
                    reinterpret_cast<const void*>(element.offset)));
                break;

            case AttribType::Int:
                GL_CHECK(glVertexAttribIPointer(
                    index,
                    element.count,
                    attribTypeToOpenGLType(element.type),
                    vboLayout.getStride(),
                    reinterpret_cast<const void*>(element.offset)));
                break;

            default:
                ASSERT(false, "Unknown base ShaderDataType!");
        }

        ++index;
    }
}


Mesh::~Mesh()
{
    GL_CHECK(glDeleteVertexArrays(1, &rendererID));
}


void Mesh::bind() const
{
    GL_CHECK(glBindVertexArray(rendererID));

    // Bind corresponding vertex and index buffers as well
    vbo->bind(); ebo->bind();
}


std::size_t Mesh::size() const
{
    return ebo->size();
}


} // namespace VoxelRaymarchDemo