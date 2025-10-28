#pragma once

#include <cstdint>
#include <string>

namespace mv
{
    typedef std::uint_fast8_t  uint8;
    typedef std::uint_fast16_t uint16;
    typedef std::uint_fast32_t uint32;
    typedef std::uint_fast64_t uint64;

    typedef std::int_fast8_t  int8;
    typedef std::int_fast16_t int16;
    typedef std::int_fast32_t int32;
    typedef std::int_fast64_t int64;

    typedef std::string String;

    struct Size 
    {
        int32 width, height;
    };

    template <class T>
    struct Vec3
    {
        T x, y, z;
    };

    using Vec3f = Vec3<float>;
    using Vec3d = Vec3<double>;

    template <class T>
    struct Vec4
    {
        T x, y, z, w;
    };

    using Vec4f = Vec4<float>;
    using Vec4d = Vec4<double>;
}