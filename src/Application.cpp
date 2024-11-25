#include "Application.h"

#include "Logging.h"


namespace VoxelRaymarchDemo
{


Application::Application()
{
    assert(!s_Instance && "Cannot create multiple instances of application!");
    Logger::log("Application started successfully.", LogLevel::INFO);
}


Application::~Application()
{
    Logger::log("Application terminated successfully.", LogLevel::INFO);
}


void Application::Run()
{
    
}


}