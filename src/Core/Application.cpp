#include "Core/Application.h"

#include "Core/Logging.h"


namespace VoxelRaymarchDemo
{

Application* Application::instance = nullptr;

// Window specifications
const int Application::windowWidth = 800;
const int Application::windowHeight = 600;
const std::string Application::windowTitle = "Voxel Raymarch Demo";

using enum LogLevel;


static void glfwErrorCallback(int error, const char* description)
{
    Logger::log<ERROR>("OpenGL error {}: {}", error, description);
}


Application::Application()
{
    // Ensure only single copy of application
    assert(!instance && "Cannot create multiple instances of Application!");
    instance = this;

    // Initialise GLFW (OpenGL library)
    if (!glfwInit())
    {
        Logger::log<FATAL>("GLFW failed to initialise!");
        std::abort();
    }

    // Specify error callback behaviour
    glfwSetErrorCallback(glfwErrorCallback);

    // Specify minimum required version of OpenGL (4.1 in this case)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Apply some OpenGL settings
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);

    // Create window
    windowHandle = glfwCreateWindow(
        windowWidth, windowHeight, windowTitle.c_str(),
        NULL, NULL // null for windowed mode, and null to not share resources with other window
    );

    if (!windowHandle)
    {
        Logger::log<FATAL>("GLFW failed to create window!");
        std::abort();
    }

    glfwMakeContextCurrent(windowHandle);

    // Initialize GLEW (OpenGL Extension Wrangler library)
    if (glewInit() != GLEW_OK)
    {
        Logger::log<FATAL>("GLEW failed to initialise!");
        std::abort();
    }

    // Initialize game instance
    game = std::make_unique<Game>();
    
    Logger::log<INFO>("Application started successfully.");

    #ifndef NDEBUG
    Logger::log<WARN>("This is a debug build!");
    #endif
}


Application::~Application()
{
    glfwDestroyWindow(windowHandle);
    Logger::log<INFO>("Application terminated successfully.");
}


void Application::run()
{
    while (!glfwWindowShouldClose(windowHandle))
    {
        glfwPollEvents();

        // Clear screen
        GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        // game->update(dt);
        game->render();

        glfwSwapBuffers(windowHandle);
    }
}


}