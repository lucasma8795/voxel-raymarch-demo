#include "Graphics/BufferLayout.h"

#include "Core/Logging.h"


namespace VoxelRaymarchDemo
{


// Size of vertex buffer attribute type in machine units.
static constexpr uint32_t attribTypeSize(AttribType type)
{
    switch (type)
    {
        case AttribType::Float:
        case AttribType::Int:
            return 4;
    }
    ASSERT(false, "Invalid AttribType!");
    std::unreachable();
}


// Convert attribute enum to string.
static std::string attribNameToString(AttribName name)
{
    switch (name)
    {
        case AttribName::Position: return "a_Position";
        // case AttribName::Normal:   return "a_Normal";
        // case AttribName::TexCoord: return "a_TexCoord";
        // case AttribName::TexelID:  return "a_TexelID";
        // case AttribName::AOLevel:  return "a_AOLevel";
    }
    ASSERT(false, "Invalid AttribName!");
    std::unreachable();
}


BufferLayout::BufferLayout(const std::initializer_list<Attribute>& attributes)
    : attributes{attributes}, stride{0}
{
    // Should not allow buffer layout of length 0
    ASSERT(!this->attributes.empty(), "Attempted to create BufferLayout of length 0!");

    for (auto& element: this->attributes)
    {
        element.offset = stride;
        stride += attribTypeSize(element.type) * element.count;
    }
}


std::vector<Attribute>::const_iterator BufferLayout::begin() const
{
    return attributes.cbegin();
}


std::vector<Attribute>::const_iterator BufferLayout::end() const
{
    return attributes.cend();
}


std::size_t BufferLayout::size() const
{
    return attributes.size();
}


uint32_t BufferLayout::getStride() const
{
    return stride;
}


}