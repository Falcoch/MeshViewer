#pragma once

#include <iostream>
#include <ostream>
#include <string_view>

namespace mv::debug
{
    void log_info(const std::string_view &);
    void log_success(const std::string_view &);
    void log_warning(const std::string_view &);
    void log_error(const std::string_view &);
    void log_fatal(const std::string_view &);

    
}