#include "Log.h"

#include "Time.h"
#include "Console.h"

namespace mv::debug 
{
    void log_info(const std::string_view & message)
    {
        std::cout << "[" << console::cyan << "Info" << console::reset << "] " << message << "\n";
    }

    void log_success(const std::string_view & message)
    {
        std::cout << "[" << console::green << "Success" << console::reset << "] " << message << "\n";
    }

    void log_warning(const std::string_view & message)
    {
        std::cerr << "[" << console::yellow << "Warning" << console::reset << "] " << message << "\n";
    }

    void log_error(const std::string_view & message)
    {
        std::cerr << "[" << console::red << "Error" << console::reset << "] " << message << "\n";
    }

    void log_fatal(const std::string_view & message)
    {
        std::cerr << "[" << console::red << "Fatal" << console::reset << "] " << message << "\n";
    }
}