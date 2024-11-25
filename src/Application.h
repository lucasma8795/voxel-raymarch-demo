#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace VoxelRaymarchDemo
{


class Application
{
public:
    Application();
    ~Application();

    // Main loop of the application.
    void Run();
    

private:
    static Application* s_Instance;

    GLFWwindow* m_WindowHandle;

    // Window specifications
    static const int s_WindowWidth;
    static const int s_WindowHeight;
    static const std::string s_WindowTitle;
};


}