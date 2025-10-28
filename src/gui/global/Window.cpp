#include "Window.h"

#include <stdexcept>
#include <iostream>

#include <utils/Log.h>

namespace mv::gui
{
    Window::Window()
    : m_window(nullptr) 
    {
        if(glfwInit() != GLFW_TRUE)
            throw std::runtime_error("Failled to initialize GLFW");

        glfwSetErrorCallback(&Private::GlfwErrorCallback);
    }

    int32 Window::width() const
    {
        if(m_window == nullptr)
            return 0;

        int width;
        glfwGetWindowSize(m_window, &width, NULL);
        return width;
    }

    int32 Window::height() const
    {
        if(m_window == nullptr)
            return 0;

        int height;
        glfwGetWindowSize(m_window, NULL, &height);
        return height;
    }

    Size Window::size() const
    {
        if(m_window == nullptr)
            return Size{0, 0};

        int width, height;
        glfwGetWindowSize(m_window, &width, &height);
        return Size{width, height};
    }

    bool Window::isOpen() const
    {
        if(m_window == nullptr)
            return false;

        return !glfwWindowShouldClose(m_window);
    }

    void Window::open(const String & title, const Size & dimension)
    {
        if(m_window != nullptr)
            return;

        m_window = glfwCreateWindow(16, 16, title.c_str(), NULL, NULL);
        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(0);

        if(m_window == nullptr)
            throw std::runtime_error("Failled to create window GLFW"); 

        GLFWmonitor * monitor = glfwGetPrimaryMonitor();
        if(monitor == NULL)
            return;
            
        const GLFWvidmode * mode = glfwGetVideoMode(monitor);
        if(dimension.width == 0 && dimension.height == 0)
            glfwSetWindowSize(m_window, 
                static_cast<int>(mode->width * 0.75), 
                static_cast<int>(mode->height * 0.75));
        else
            glfwSetWindowSize(m_window, 
                dimension.width, 
                dimension.height);

        Size current_size = size();
        glfwSetWindowPos(m_window, 
            static_cast<int>((mode->width - current_size.width) * 0.5), 
            static_cast<int>((mode->height - current_size.height) * 0.5));
    }

    void Window::close()
    {
        if(m_window == nullptr)
            return;

        glfwSetWindowShouldClose(m_window, true);
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    void Window::pollevents()
    {
        glfwPollEvents();
    }

    void Window::swapbuffers()
    {
        if(m_window == nullptr)
            return;

        glfwSwapBuffers(m_window);
    }

    GLFWwindow * Window::operator&() const
    {
        return m_window;
    }

    namespace Private
    {
        void  GlfwErrorCallback(int error, const char* description)
        {
            debug::log_error("[GLFW] " + std::to_string(error) + ": " + std::string(description));
        }
    }
}