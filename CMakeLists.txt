# cmake .. -G "MinGW Makefiles" -DCMAKE_C_COMPILER="clang.exe" -DCMAKE_CXX_COMPILER="clang++.exe"
# cmake -A x64 -T ClangCL ..

#===========================================================================================#
#                                  CMake Configuration                                      #
#===========================================================================================#

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#===========================================================================================#
#                                         Compiler                                          #
#===========================================================================================#

#===========================================================================================#
#                                       Project                                             #
#===========================================================================================#

set(PROJECT_NAME "Mesh Viewer")
set(EXECUTABLE_NAME "MeshViewer")

#===========================================================================================#
#                                       Sources                                             #
#===========================================================================================#

set(_src_dir_ ${CMAKE_SOURCE_DIR}/src/)
set(_lib_dir_ ${CMAKE_SOURCE_DIR}/lib/)
set(_inc_dir_ ${CMAKE_SOURCE_DIR}/inc/)

#===========================================================================================#
#                                       Project                                             #
#===========================================================================================#

project(${PROJECT_NAME})
set(TARGET ${EXECUTABLE_NAME})

add_executable(${TARGET})

set(_main_source
    src/main.cpp
)

set(_header
    src/engine/GLSession.h
    src/engine/ImGuiSession.h
    src/engine/back/buffer/Buffer.h
    src/engine/back/buffer/EditMode.h
    src/engine/back/buffer/GenericBuffer.h
    src/engine/back/buffer/Layout.h
    src/engine/back/buffer/VertexArray.h
    src/engine/back/buffer/VerticeBuffer.h
    src/engine/back/shader/Program.h
    src/engine/back/shader/Source.h
    src/engine/back/shader/File.h
    src/engine/back/texture/Texture.h

    src/gui/global/Window.h

    src/utils/Color.h
    src/utils/Console.h
    src/utils/Log.h
    src/utils/Macro.h
    src/utils/Singleton.h
    src/utils/Std.h
    src/utils/Time.h
    src/utils/Type.h
    src/utils/Image.h
)

set(_source
    ${_main_source}
    src/engine/GLSession.cpp
    src/engine/ImGuiSession.cpp
    src/engine/back/buffer/Buffer.cpp
    src/engine/back/buffer/EditMode.cpp
    src/engine/back/buffer/GenericBuffer.tpp
    src/engine/back/buffer/Layout.cpp
    src/engine/back/buffer/VertexArray.cpp
    src/engine/back/buffer/VerticeBuffer.cpp
    src/engine/back/shader/Program.cpp
    src/engine/back/shader/Source.cpp
    src/engine/back/shader/File.cpp
    src/engine/back/texture/Texture.cpp

    src/gui/global/Window.cpp

    src/utils/Color.cpp
    src/utils/Console.cpp
    src/utils/Log.cpp
    src/utils/Macro.cpp
    src/utils/Time.cpp
    src/utils/Image.cpp
)

target_sources(${TARGET} PRIVATE ${_header} ${_source})

set_property(TARGET ${TARGET} PROPERTY RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>)

#===========================================================================================#
#                                       Project                                             #
#===========================================================================================#

target_include_directories(${TARGET} PRIVATE ${_src_dir_})
target_sources(${TARGET} PRIVATE ${_header} ${_source})

find_package(OpenGL REQUIRED)
target_link_libraries(${TARGET} PRIVATE OpenGL::GL)

find_package(glfw3 REQUIRED)
target_link_libraries(${TARGET} PRIVATE glfw)

find_package(GLEW REQUIRED)
target_link_libraries(${TARGET} PRIVATE GLEW::GLEW)

find_package(glm REQUIRED)
target_link_libraries(${TARGET} PRIVATE glm::glm-header-only)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${TARGET} PRIVATE imgui::imgui)

find_package(glaze CONFIG REQUIRED)
target_link_libraries(${TARGET} PRIVATE glaze::glaze)