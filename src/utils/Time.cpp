#include "Time.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace mv::debug 
{
    time_t current_time_t()
    {
        auto now = std::chrono::system_clock::now();
        return std::chrono::system_clock::to_time_t(now);
    }

    std::string current_time(const std::string & format) 
    {
        time_t now = current_time_t();
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&now), format.c_str());
        return oss.str();
    }
}