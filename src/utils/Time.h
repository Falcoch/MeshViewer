#pragma once

#include <string>

namespace mv::debug 
{
    time_t current_time_t();
    std::string current_time(const std::string & = "%H:%M:%S");
}