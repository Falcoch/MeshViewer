#pragma once

#include <GLFW/glfw3.h>

#include <utils/Type.h>

namespace mv::gui
{
    class Window 
    {
        public:
            Window();
           ~Window() = default;

            int32 width() const;
            int32 height() const;
            Size size() const;

            bool isOpen() const;

            void open(const String &, const Size & = {0, 0});
            void close();

            void pollevents();
            void swapbuffers();

            GLFWwindow * operator&() const;

        private:
            GLFWwindow * m_window;
    };

    namespace Private
    {
        void GlfwErrorCallback(int error, const char* description);
    }
}