#include "Graphics/ShaderProgram.h"

#include "Core/Logging.h"


namespace VoxelRaymarchDemo
{


ShaderProgram::ShaderProgram(const std::string& vertexFilePath,
                             const std::string& fragmentFilePath)
{
    using enum LogLevel;

    // Compile shaders
    RendererID vertexShader = compileShader(GL_VERTEX_SHADER, vertexFilePath);
    RendererID fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentFilePath);

    // Link shaders to form program
    GL_CHECK(rendererID = glCreateProgram());
    GL_CHECK(glAttachShader(rendererID, vertexShader));
    GL_CHECK(glAttachShader(rendererID, fragmentShader));
    GL_CHECK(glLinkProgram(rendererID));

    // Check if program successfully linked
    GLint isLinked = 0;
    GL_CHECK(glGetProgramiv(rendererID, GL_LINK_STATUS, &isLinked));
    if (isLinked == GL_FALSE)
    {
        // Obtain error information
        GLint maxLength = 0;
        GL_CHECK(glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &maxLength));
        std::vector<GLchar> infoLog(maxLength);
        GL_CHECK(glGetProgramInfoLog(rendererID, maxLength, &maxLength, &infoLog[0]));
        
        // Get rid of everything
        GL_CHECK(glDeleteProgram(rendererID));
        GL_CHECK(glDeleteShader(vertexShader));
        GL_CHECK(glDeleteShader(fragmentShader));
        
        // Output error
        Logger::log<ERROR>("Shaders at '{}' and '{}' failed to link!",
                           vertexFilePath, fragmentFilePath);
    }
    else
    {
        Logger::log<INFO>("Shaders at '{}' and '{}' compiled successfully.",
                          vertexFilePath, fragmentFilePath);
    }

    // Detach shaders
    GL_CHECK(glDeleteShader(vertexShader));
    GL_CHECK(glDeleteShader(fragmentShader));
}


ShaderProgram::~ShaderProgram()
{
    // Delete shader program
    GL_CHECK(glDeleteProgram(rendererID));
}


RendererID ShaderProgram::compileShader(GLenum shaderType, const std::string& filePath) noexcept
{
    // Read shader file
    std::ifstream fileStream(filePath.c_str());
    std::string source(std::istreambuf_iterator<char>{fileStream},
                       std::istreambuf_iterator<char>{});

    // Compile shader
    RendererID shader; GL_CHECK(shader = glCreateShader(shaderType));
    const GLchar* sourcePtr = source.c_str();
    GL_CHECK(glShaderSource(shader, 1, &sourcePtr, 0));
    GL_CHECK(glCompileShader(shader));

    // Check if compilation success
    GLint isCompiled = 0;
    GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled));

    if (isCompiled == GL_FALSE)
    {
        // Obtain error information
        GLint maxLength = 0;
        GL_CHECK(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength));
        std::vector<GLchar> infoLog(maxLength);
        GL_CHECK(glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]));
        
        // Get rid of shader
        GL_CHECK(glDeleteShader(shader));

        // Output error
        std::cerr << "Shader at `" << filePath << "` failed to compile!" << std::endl;
        std::cerr << infoLog.data() << std::endl;
        std::abort();
    }

    return shader;
}





}