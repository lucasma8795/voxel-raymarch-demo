#pragma once

#include "Graphics/ShaderProgram.h"
#include "Graphics/Mesh.h"


namespace VoxelRaymarchDemo
{


class Game
{
public:
    Game();

    void update(float dt);

    void render();


private:
    std::unique_ptr<ShaderProgram> shader;
    std::unique_ptr<Mesh> mesh;
};


}