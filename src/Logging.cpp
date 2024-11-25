#include "Logging.h"


namespace VoxelRaymarchDemo
{


// Helper to return prefix of a log message
static std::string prefix()
{
    auto now = std::chrono::system_clock::now();
    return std::format("[{0:%F_%T}]", now);
}


void Logger::log(std::string msg, LogLevel level)
{
    // TODO(lucas): add colouring for log levels
    std::cout << prefix() << ' ' << msg << std::endl;
}


}