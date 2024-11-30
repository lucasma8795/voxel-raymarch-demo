#pragma once

#include "Game/Game.h"


namespace VoxelRaymarchDemo
{


class Application
{
public:
    Application();
    ~Application();

    // Main loop of the application.
    void run();
    

private:
    static Application* instance;

    GLFWwindow* windowHandle;

    std::unique_ptr<Game> game;

    // Window specifications
    static const int windowWidth;
    static const int windowHeight;
    static const std::string windowTitle;
};


}