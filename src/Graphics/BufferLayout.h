#pragma once


namespace VoxelRaymarchDemo
{


// Vertex buffer layout attribute names.
enum class AttribName
{
    Position,  // a_Position
    // Normal,    // a_Normal
    // TexCoord,  // a_TexCoord
};


// Vertex buffer layout attribute base types.
enum class AttribType
{
    Float,
    Int
};


// Vertex buffer layout attribute.
struct Attribute
{
    AttribName name;
    uint32_t count;
    AttribType type;
    uint32_t offset = 0;
    bool normalized = false;

    constexpr Attribute(AttribName name, uint32_t count, AttribType type, bool normalized=false)
        : name{name}, count{count}, type{type}, normalized{normalized}
    {}
};


// Vertex buffer layout.
class BufferLayout
{
public:
    BufferLayout(const std::initializer_list<Attribute>& attributes);

    std::vector<Attribute>::const_iterator begin() const;
    std::vector<Attribute>::const_iterator end() const;
    std::size_t size() const;

    uint32_t getStride() const;


private:
    std::vector<Attribute> attributes;
    uint32_t stride;
};


constexpr GLenum attribTypeToOpenGLType(AttribType type)
{
    switch (type)
    {
        case AttribType::Float: return GL_FLOAT;
        case AttribType::Int:   return GL_INT;
    }
    ASSERT(false, "Invalid AttribType!");
    std::unreachable();
}


}