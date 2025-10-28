#include <iostream>

#include "utils/Log.h"
#include "utils/Time.h"
#include "utils/Color.h"

#include "engine/GLSession.h"
#include "engine/ImGuiSession.h"

#include "engine/back/buffer/VerticeBuffer.h"

int main(int, char **)
{
    try 
    {
        mv::gui::Window window;
        window.open("Mesh Viewer");

        mv::GLSession::Instance().initialize(window);
        mv::ImGuiSession::Instance().initialize(window);

        mv::debug::log_info("Initialize Buffer");

        mv::engine::VertexArray vao;
        vao.bind();

        mv::engine::VerticeBuffer vbo(vao, {{mv::engine::Layout::XYZ, 3}}, 255);
        vbo.bind();

        mv::debug::log_info("Initialize Shaders");

        // TODO

        mv::debug::log_info("Loop begin");
        while(window.isOpen())
        {
            window.pollevents();
            window.swapbuffers();
        }
        mv::debug::log_info("Loop end");

        return EXIT_SUCCESS;
    }
    catch(std::exception & error)
    {
        mv::debug::log_fatal(error.what());
    }

    return EXIT_FAILURE;
}