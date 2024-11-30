#pragma once


namespace VoxelRaymarchDemo
{


// Base class for OpenGL buffers.
template<GLenum Target>
class Buffer
{
public:
    Buffer();
    ~Buffer();

    // Do not allow copies of buffer (since destructor will free the buffer)
    Buffer(const Buffer&) = delete;
    Buffer operator=(const Buffer&) = delete;

    void bind() const;

    std::size_t size() const;

    template<typename T> void bufferData(const std::vector<T>& data);


private:
    RendererID rendererID;
    std::size_t numElements;
};


using VertexBuffer = Buffer<GL_ARRAY_BUFFER>;
using IndexBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;


template<GLenum Target>
template<typename T>
inline void Buffer<Target>::bufferData(const std::vector<T>& data)
{
    bind();

    numElements = data.size();
    std::ptrdiff_t bytes = sizeof(T) * numElements;
    GL_CHECK(glBufferData(Target, bytes, data.data(), GL_STATIC_DRAW));
}


}