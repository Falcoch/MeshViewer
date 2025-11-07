#include <iostream>

#define MV_TYPE_INT_USE_FAST

#include "utils/Log.h"
#include "utils/Time.h"
#include "utils/Color.h"

#include "engine/GLSession.h"
#include "engine/ImGuiSession.h"

#include "engine/back/buffer/VerticeBuffer.h"
#include "engine/back/shader/Program.h"

int main(int, char **)
{
    try 
    {
        mv::gui::Window window;
        window.open("Mesh Viewer");

        mv::GLSession::Instance().initialize(window);
        mv::ImGuiSession::Instance().initialize(window);

        mv::debug::log_info("Initialize buffer");

        mv::engine::VertexArray vao;
        vao.bind();

        mv::engine::VerticeBuffer vbo(vao, {{mv::engine::layout::Value::XYZ, mv::engine::layout::defaults::Weight::XYZ}}, 255);
        vbo.bind();

        vbo.set(
            {
                -0.5f, -0.5f, 0.0f, 
                 0.5f, -0.5f, 0.0f,
                -0.5f,  0.5f, 0.0f
            }
        );

        mv::debug::log_info("Initialize shaders");
        mv::debug::log_info("Loading vertex shader");

        mv::engine::shader::Source vertex;
        vertex << mv::engine::shader::File(mv::engine::shader::File::Type::Vertex, "./src/shader/basic/Basic.vert");

        mv::debug::log_info("Loading fragment shader");

        mv::engine::shader::Source fragment;
        fragment << mv::engine::shader::File(mv::engine::shader::File::Type::Fragment, "./src/shader/basic/Basic.frag");

        mv::debug::log_info("Attaching shaders");
        mv::engine::shader::Program program;
        program << vertex;
        program << fragment;

        mv::debug::log_info("Linking program");
        program.link();

        mv::debug::log_info("Loop begin");
        while(window.isOpen())
        {
            window.pollevents();
            program.use();
            glDrawArrays(GL_TRIANGLES, 0, 3);
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