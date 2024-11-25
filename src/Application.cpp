#include "Application.h"

#include "Logging.h"


namespace VoxelRaymarchDemo
{

Application* Application::s_Instance = nullptr;

// Window specifications
const int Application::s_WindowWidth = 800;
const int Application::s_WindowHeight = 600;
const std::string Application::s_WindowTitle = "Voxel Raymarch Demo";


static void glfwErrorCallback(int error, const char* description)
{
    std::string msg = std::format("OpenGL error {}: {}", error, description);
    Logger::log(msg, LogLevel::ERROR);
}


Application::Application()
    : m_WindowHandle{nullptr}
{
    // Ensure only single copy of application
    assert(!s_Instance && "Cannot create multiple instances of Application!");
    s_Instance = this;

    // Initialise GLFW (OpenGL library)
    if (!glfwInit())
    {
        Logger::log("GLFW failed to initialise!", LogLevel::FATAL);
        std::abort();
    }

    // Specify error callback behaviour
    glfwSetErrorCallback(glfwErrorCallback);

    // Specify minimum required version of OpenGL (4.1 in this case)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    m_WindowHandle = glfwCreateWindow(
        s_WindowWidth, s_WindowHeight, s_WindowTitle.c_str(),
        NULL, NULL // null for windowed mode, and null to not share resources with other window
    );

    if (!m_WindowHandle)
    {
        Logger::log("GLFW failed to create window!", LogLevel::FATAL);
        std::abort();
    }

    glfwMakeContextCurrent(m_WindowHandle);
    
    Logger::log("Application started successfully.", LogLevel::INFO);
}


Application::~Application()
{
    glfwDestroyWindow(m_WindowHandle);
    Logger::log("Application terminated successfully.", LogLevel::INFO);
}


void Application::Run()
{
    while (!glfwWindowShouldClose(m_WindowHandle))
    {
        glfwPollEvents();
        glfwSwapBuffers(m_WindowHandle);
    }
}


}