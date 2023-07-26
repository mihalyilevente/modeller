cmake_minimum_required(VERSION 3.17)
project(modeller)

set(CMAKE_CXX_STANDARD 14)

include_directories(external/GLAD/include)
include_directories(external/GLM)
include_directories(external/imgui)  # Add ImGui header files path here

find_package(OpenGL REQUIRED)
# Find GLFW library
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

# Add ImGui source files to a library
add_library(ImGui
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_demo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_tables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.cpp
        )


add_executable(
        modeller main.cpp external/GLAD/src/glad.c calss/Window.cpp calss/Window.h
        calss/Buffer.cpp calss/Buffer.h calss/Shader.cpp calss/Shader.h
        calss/Camera.cpp calss/Camera.h calss/ObjLoader.cpp calss/ObjLoader.h
        calss/InputHandler.cpp calss/InputHandler.h calss/Texture.cpp calss/Texture.h
        external/STB/stb_image.h calss/Object.cpp calss/Object.h calss/lib.h
)

# Link libraries to your project
target_link_libraries(modeller ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ImGui)
