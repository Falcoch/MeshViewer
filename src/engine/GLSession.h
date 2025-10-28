#pragma once

#include <GL/glew.h>

#include "../gui/global/Window.h"
#include "../utils/Singleton.h"

namespace mv
{
    class GLSession : public Singleton<GLSession>
    { 
        public:
            GLSession() = default;
   virtual ~GLSession() = default;

            void initialize(const gui::Window &);
    };
}