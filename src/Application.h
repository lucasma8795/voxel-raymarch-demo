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
};


}