#include "ImGuiSession.h"

#include <stdexcept>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

namespace mv 
{
    void ImGuiSession::initialize(const gui::Window & window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        io().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(&window, true);
    }

    ImGuiIO & ImGuiSession::io()
    {
        return ImGui::GetIO();
    }

    ImGuiStyle & ImGuiSession::style()
    {
        return ImGui::GetStyle();
    }

    /*
    void ImGuiSession::begin_frame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiSession::end_frame()
    {
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    */
}