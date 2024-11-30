#include "Game.h"


namespace VoxelRaymarchDemo
{


Game::Game()
{
    // Compile shader program
    shader = std::make_unique<ShaderProgram>("assets/shaders/main.vert",
                                             "assets/shaders/main.frag");
    
    // Create fullscreen quad mesh
    static const BufferLayout bufferLayout =
        {{AttribName::Position, 3, AttribType::Float}};

    static const std::vector<glm::vec3> vertices = 
    {
        glm::vec3(-1.0f, -1.0f,  0.0f),
        glm::vec3(-1.0f,  1.0f,  0.0f),
        glm::vec3( 1.0f,  1.0f,  0.0f),
        glm::vec3( 1.0f, -1.0f,  0.0f)
    };

    static const std::vector<uint32_t> indices = {0, 2, 1, 0, 3, 2};

    auto vbo = std::make_unique<VertexBuffer>();
    auto ebo = std::make_unique<IndexBuffer>();

    vbo->bufferData(vertices);
    ebo->bufferData(indices);

    mesh = std::make_unique<Mesh>(std::move(vbo), std::move(ebo), bufferLayout);
}


void Game::update(float dt)
{
    // no-op (for now!)
}


void Game::render()
{
    mesh->bind();
    shader->bind();

    GL_CHECK(glDrawElements(GL_TRIANGLES, mesh->size(), GL_UNSIGNED_INT, nullptr));
}


}