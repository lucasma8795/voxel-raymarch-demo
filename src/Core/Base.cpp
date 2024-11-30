#include "Core/Base.h"

#include <execinfo.h>
#include <unistd.h>


namespace VoxelRaymarchDemo
{


[[noreturn]]
void impl::assertionFailure(const std::string_view msg,
                            const std::source_location loc)
{
    std::cerr << loc.file_name()
              << '(' << loc.line() << ':' << loc.column() << ") `"
              << loc.function_name() << "`: "
              << msg << std::endl;

    // std::cerr << std::stacktrace::current() << std::endl;

    // Dump stack trace information
    // https://stackoverflow.com/questions/77005/how-to-automatically-generate-a-stacktrace-when-my-program-crashes
    std::cerr << "Traceback: (most recent call first)" << std::endl;
    void* tb_array[128];
    int tb_length = backtrace(tb_array, 128);
    backtrace_symbols_fd(tb_array, tb_length, STDERR_FILENO);

    std::abort();
}


}