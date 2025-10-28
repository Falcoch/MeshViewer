#include "Console.h"

namespace mv::console
{
    std::ostream & operator<<(std::ostream & os, Private::Color code) 
    {   
        #ifdef MV_OS_WINDOWS
            HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(output, code);
        #else
        #ifdef MV_OS_LINUX
            os << "\033[" << code << "m"; 
        #else
            os << code << ": ";
        #endif
        #endif
        return os;
    }

    std::ostream & red(std::ostream & os)
    {
        return os << Private::Color::RED;
    }

    std::ostream & green(std::ostream & os)
    {
        return os << Private::Color::GREEN;
    }

    std::ostream & blue(std::ostream & os)
    {
        return os << Private::Color::BLUE;
    }

    std::ostream & yellow(std::ostream & os)
    {
        return os << Private::Color::YELLOW;
    }

    std::ostream & purple(std::ostream & os)
    {
        return os << Private::Color::PURPLE;
    }

    std::ostream & cyan(std::ostream & os)
    {
        return os << Private::Color::CYAN;
    }

    std::ostream & white(std::ostream & os)
    {
        return os << Private::Color::WHITE;
    }

    std::ostream & black(std::ostream & os)
    {
        return os << Private::Color::BLACK;
    }

    std::ostream & reset(std::ostream & os)
    {
        #ifdef MV_OS_WINDOWS
        return (os << white);
        #else
        #ifdef MV_OS_LINUX
        return console::operator<<(os, 39);
        #endif
        #endif
    }
}