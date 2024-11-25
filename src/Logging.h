namespace VoxelRaymarchDemo
{


// Define severity of log message
enum class LogLevel { INFO, WARN, ERROR, FATAL };


// Simple static class implementation of a logger.
class Logger
{
public:
    Logger() = delete;

    static void log(std::string msg, LogLevel level);
};


}