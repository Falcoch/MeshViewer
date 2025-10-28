#pragma once

#include <ostream>

#include <windows.h>

#include "Macro.h"

namespace mv::console
{
    namespace Private 
    {
        enum Color;
        #ifdef MV_OS_WINDOWS
        enum Color : uint32_t
        {
            RED     = FOREGROUND_RED   | FOREGROUND_INTENSITY,
            GREEN   = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
            BLUE    = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
            YELLOW  = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
            PURPLE  = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
            CYAN    = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
            WHITE   = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_GREEN,
            BLACK   = 0,
        };
        #else
        #ifdef MV_OS_LINUX
        enum Color : uint32_t
        {
            RED     = 91,
            GREEN   = 92,
            BLUE    = 94,
            YELLOW  = 93,
            PURPLE  = 95,
            CYAN    = 96,
            WHITE   = 97,
            BLACK   = 30
        }
        #else
        enum Color : uint3_t
        {
            RED     = 'r',
            GREEN   = 'g',
            BLUE    = 'b',
            YELLOW  = 'y',
            PURPLE  = 'p',
            CYAN    = 'c',
            WHITE   = 'W',
            BLACK   = 'B'
        }
        #endif
        #endif
    }
    
    std::ostream & operator<<(std::ostream &, Private::Color);

    std::ostream & red(std::ostream &);
    std::ostream & green(std::ostream &);
    std::ostream & blue(std::ostream &);
    std::ostream & yellow(std::ostream &);
    std::ostream & purple(std::ostream &);
    std::ostream & cyan(std::ostream &);
    std::ostream & white(std::ostream &);
    std::ostream & black(std::ostream &);
    std::ostream & reset(std::ostream &);
}