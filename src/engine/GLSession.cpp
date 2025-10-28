#include "GLSession.h"

#include <stdexcept>
#include <utils/Log.h>

namespace mv 
{
    void GLSession::initialize(const gui::Window & window)
    {
        if(!window.isOpen())
            throw std::runtime_error("Window is not open");

        if(glewInit())
            throw std::runtime_error("Cannot initialize GLEW");

        Size dimension = window.size();
        glViewport(0, 0, dimension.width, dimension.height);
    }
}