#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define MV_TYPE_INT_USE_FAST

#include "utils/Log.h"
#include "utils/Time.h"
#include "utils/Color.h"

#include "engine/GLSession.h"
#include "engine/ImGuiSession.h"

#include "engine/back/buffer/VerticeBuffer.h"
#include "engine/back/shader/Program.h"
#include "engine/back/texture/Texture.h"
#include "engine/back/camera/FreeCamera.h"

int main(int, char **)
{
    try 
    {
        mv::gui::Window window;
        window.open("Mesh Viewer");

        
        mv::Image icon;
        icon.load("./assets/icon/ico32.png");
        window.changeIcon(icon);
        icon.release();

        mv::GLSession::Instance().initialize(window);
        mv::ImGuiSession::Instance().initialize(window);

        mv::debug::log_info("Initialize buffer");

        mv::engine::VertexArray vao;
        vao.bind();

        mv::engine::VerticeBuffer vbo(vao, {
            {mv::engine::layout::Value::XYZ, mv::engine::layout::defaults::Weight::XYZ},
            {mv::engine::layout::Value::UV,  mv::engine::layout::defaults::Weight::UV}
        
        }, 255);

        vbo.bind();
        vbo.set(
            {
                -0.5f, -0.5f, 0.0f,     0.f, 1.f,
                 0.5f, -0.5f, 0.0f,     1.f, 1.f,
                -0.5f,  0.5f, 0.0f,     0.f, 0.f,

                 0.5f, -0.5f, 0.0f,     1.f, 1.f,
                 0.5f,  0.5f, 0.0f,     1.f, 0.f,
                -0.5f,  0.5f, 0.0f,     0.f, 0.f
            }
        );

        mv::debug::log_info("Initialize shaders");
        mv::debug::log_info("Loading vertex shader");

        mv::engine::shader::Source vertex;
        vertex << mv::engine::shader::File(mv::engine::shader::File::Type::Vertex, "./src/shader/basic/Camera_Texture.vert");

        mv::debug::log_info("Loading fragment shader");

        mv::engine::shader::Source fragment;
        fragment << mv::engine::shader::File(mv::engine::shader::File::Type::Fragment, "./src/shader/basic/Camera_Texture.frag");

        mv::debug::log_info("Attaching shaders");
        mv::engine::shader::Program program;
        program << vertex;
        program << fragment;

        mv::debug::log_info("Linking program");
        program.link();

        mv::debug::log_info("Loading texture");
        mv::Image image;
        image.load("./assets/texture/test/HelloThere.png");

        mv::engine::Texture texture(image);
        texture.bind(0);

        image.release();

        mv::debug::log_info("Initialize Camera");
        mv::engine::FreeCamera camera;
        camera.setRatio(window.width(), window.height());

        mv::debug::log_info("Loop begin");
        while(window.isOpen())
        {
            window.pollevents();
            program.use();
            program.setUniform("uSlot", 0);
            program.setUniform("uProj", camera.projection());
            program.setUniform("uView", camera.view());
            program.setUniform("uModel", glm::mat4x4(1.f));

            glDrawArrays(GL_TRIANGLES, 0, 6);
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