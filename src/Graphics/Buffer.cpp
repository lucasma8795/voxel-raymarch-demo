#include "Graphics/Buffer.h"


namespace VoxelRaymarchDemo
{


// Explicit instantiations
template class Buffer<GL_ARRAY_BUFFER>;
template class Buffer<GL_ELEMENT_ARRAY_BUFFER>;


template<GLenum Target>
Buffer<Target>::Buffer()
    : numElements{0u}
{
    GL_CHECK(glGenBuffers(1, &rendererID));
}


template<GLenum Target>
Buffer<Target>::~Buffer()
{
    GL_CHECK(glDeleteBuffers(1, &rendererID));
}


template<GLenum Target>
void Buffer<Target>::bind() const
{
    GL_CHECK(glBindBuffer(Target, rendererID));
}


template<GLenum Target>
std::size_t Buffer<Target>::size() const
{
    return numElements;
}


}