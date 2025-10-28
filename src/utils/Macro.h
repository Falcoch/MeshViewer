#pragma once

#include <string>

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    #define MV_OS_WINDOWS
#else
#if defined(unix) || defined(__unix) || defined(__unix__) 
    #define MV_OS_UNIX
#else
#if defined(__APPLE__) || defined(__MACH__)
    #define MV_OS_MACOS
#else
#if defined(__linux__) 
    #define MV_OS_LINUX
#else
    #define MV_OS_UNKNOWN
#endif
#endif
#endif
#endif

namespace mv::macro
{
    inline std::string os_string()
    {
        #ifdef MV_OS_WINDOWS
            return "OS_Windows";
        #else
        #ifdef MV_OS_UNIX
            return "OS_Unix";
        #else
        #ifndef MV_OS_MACOS
            return "OS_MacOs";
        #else
        #ifndef MV_OS_LINUX
            return "OS_Linux";         
        #endif
        #endif
        #endif
        #endif    
        return "OS_Unknown";
    }
}
