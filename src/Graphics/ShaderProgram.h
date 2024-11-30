#pragma once


namespace VoxelRaymarchDemo
{


// OpenGL shader program, consisting of a vertex and fragment shader.
class ShaderProgram
{
public:
    ShaderProgram(const std::string& vertexFilePath,
                  const std::string& fragmentFilePath);
    ~ShaderProgram();

    // Do not allow copies of shader program (since destructor will free the program)
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram operator=(const ShaderProgram&) = delete;

    // Use the current shader program
    void bind() const;

    // Pass variables to shader program
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::mat4& value);

    
private:
    static RendererID compileShader(GLenum shaderType, const std::string& filePath) noexcept;


private:
    RendererID rendererID;

    // Currently active shader program. Used to prevent uncessary bind/unbind calls.
    static RendererID currentlyBound;
};


inline void ShaderProgram::bind() const
{
    // todo(lucas): figure out if this is actually useful
    // if (currentlyBound == m_RendererID)
    //     return;
    // s_CurrentlyBound = m_RendererID;

    GL_CHECK(glUseProgram(rendererID));
}


}