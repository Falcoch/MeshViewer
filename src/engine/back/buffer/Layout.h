#pragma once

#include <utils/Type.h>
#include <vector>

namespace mv::engine::Layout
{
    enum  Value
    {
        XYZ,
        RGB,
        UV,
        NORM,
    };

    struct Unit
    {
        Value value;
        uint64 weight;

        friend bool operator==(const Unit & a, const Unit & b) 
        {
            return a.value == b.value;
        }
    };

    typedef std::vector<Unit> Array;

    inline uint64 weight(const Array & array)
    {
        uint64 total = 0;
        for(auto & unit : array)
            total += unit.weight;

        return total;
    }
}