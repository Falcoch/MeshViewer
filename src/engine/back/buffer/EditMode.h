#pragma once

#include <GL/glew.h>
#include <stdint.h>

namespace mv::engine 
{
    enum EditMode 
    {
        DYNAMIC = GL_DYNAMIC_DRAW,
        STATIC  = GL_STATIC_DRAW
    };
}