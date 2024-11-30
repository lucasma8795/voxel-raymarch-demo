#pragma once


namespace VoxelRaymarchDemo
{


using RendererID = uint32_t;


// Debug utilities

namespace impl
{

[[noreturn]]
void assertionFailure(const std::string_view msg,
                      const std::source_location loc = std::source_location::current());

}

#ifdef NDEBUG
    #define ASSERT(...) (void(0))
    #define GL_CHECK(stmt) stmt
#else
    #define ASSERT(cond, fmt, ...) \
        __builtin_expect(!(cond), 0) \
            ? impl::assertionFailure(std::format(fmt, ##__VA_ARGS__)) \
            : ((void)0)
    #define GL_CHECK(stmt) \
        {stmt; GLenum err = glGetError(); \
        ASSERT(err == GL_NO_ERROR, "OpenGL error code {}!", err);}
#endif


}