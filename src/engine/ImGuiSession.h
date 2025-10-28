#pragma once

#include <GL/glew.h>
#include <imgui.h>

#include "../gui/global/Window.h"
#include "../utils/Singleton.h"

namespace mv
{
    class ImGuiSession : public Singleton<ImGuiSession>
    { 
        public:
            ImGuiSession() = default;
   virtual ~ImGuiSession() = default;

            void initialize(const gui::Window &);

            ImGuiIO & io();
            ImGuiStyle & style();

            //void begin_frame();
            //void end_frame();
    };
}