#pragma once

#include <cstdint>
#include <string>
#include <filesystem>

#define MV_TYPE_PREDEFINED_VEC

#ifdef MV_TYPE_PREDEFINED_VEC
    #define  MV_TYPE_PREDEFINED_VEC2
    #define  MV_TYPE_PREDEFINED_VEC3
    #define  MV_TYPE_PREDEFINED_VEC4
#endif

namespace mv
{
    #ifdef MV_TYPE_INT_USE_FAST
        typedef std::uint_fast8_t  uint8;
        typedef std::uint_fast16_t uint16;
        typedef std::uint_fast32_t uint32;
        typedef std::uint_fast64_t uint64;

        typedef std::int_fast8_t  int8;
        typedef std::int_fast16_t int16;
        typedef std::int_fast32_t int32;
        typedef std::int_fast64_t int64;
    #else
    #ifdef MV_TYPE_INT_USE_LEAST
        typedef std::uint_least8_t  uint8;
        typedef std::uint_least16_t uint16;
        typedef std::uint_least32_t uint32;
        typedef std::uint_least64_t uint64;

        typedef std::int_least8_t  int8;
        typedef std::int_least16_t int16;
        typedef std::int_least32_t int32;
        typedef std::int_least64_t int64;
    #else
        typedef std::uint8_t  uint8;
        typedef std::uint16_t uint16;
        typedef std::uint32_t uint32;
        typedef std::uint64_t uint64;

        typedef std::int8_t  int8;
        typedef std::int16_t int16;
        typedef std::int32_t int32;
        typedef std::int64_t int64;
    #endif
    #endif

    #ifdef MV_TYPE_REDIFINED_BOOLS
        constexpr int8 False = 0;
        constexpr int8 True  = 1;
    #endif

    typedef std::string String;
    typedef std::filesystem::path Path;

    struct Size 
    {
        int32 width, height;
    };

    template <class T>
    struct Vec2 
    {
        T x, y;
    };

    #ifdef MV_TYPE_PREDEFINED_VEC2
        using Vec2i = Vec2<int32>;
        using Vec2f = Vec2<float>;
        using Vec2d = Vec2<double>;
    #endif

    template <class T>
    struct Vec3
    {
        T x, y, z;
    };

    #ifdef MV_TYPE_PREDEFINED_VEC3
        using Vec3i = Vec3<int32>;
        using Vec3f = Vec3<float>;
        using Vec3d = Vec3<double>;
    #endif

    template <class T>
    struct Vec4
    {
        T x, y, z, w;
    };

    #ifdef MV_TYPE_PREDEFINED_VEC4
        using Vec4i = Vec4<int32>;
        using Vec4f = Vec4<float>;
        using Vec4d = Vec4<double>;
    #endif
}