#pragma once


namespace VoxelRaymarchDemo
{


// Define severity of log message
enum class LogLevel { INFO, WARN, ERROR, FATAL };


// Simple static class implementation of a logger.
class Logger
{
public:
    Logger() = delete;

    template<LogLevel T, typename... Args>
    static void log(std::format_string<Args...> fmt, Args&&... args);
};


namespace impl
{

// Helper to return time prefix of a log message
inline std::string timePrefix()
{
    auto now = std::chrono::system_clock::now();
    return std::format("[{0:%F_%T}]", now);
}

}


template<LogLevel Level, typename... Args>
void Logger::log(std::format_string<Args...> fmt, Args&&... args)
{
    using enum LogLevel;
    std::string colorPrefix, colorSuffix;

    if constexpr (Level != INFO)
        colorSuffix = "\x1b[0m";

    if constexpr (Level == WARN)
        colorPrefix = "\x1b[1;95m";
    else if constexpr (Level == ERROR)
        colorPrefix = "\x1b[1;91m";
    else if constexpr (Level == FATAL)
        colorPrefix = "\x1b[1;91m";
    

    std::cout << colorPrefix
              << impl::timePrefix() << ' '
              << std::format(fmt, std::forward<Args>(args)...)
              << colorSuffix << std::endl;
}


}