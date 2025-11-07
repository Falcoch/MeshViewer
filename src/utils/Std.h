#pragma once

#include <string>
#include <algorithm>

namespace std
{
    std::string to_lower(std::string data)
    {
        std::transform(data.begin(), data.end(), data.begin(),
            [](unsigned char c)
            { 
                return std::tolower(c); 
            });

        return data;
    }

    std::string to_upper(std::string data)
    {
        std::transform(data.begin(), data.end(), data.begin(),
            [](unsigned char c)
            { 
                return std::toupper(c); 
            });

        return data;
    }
}