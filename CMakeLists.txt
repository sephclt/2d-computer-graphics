cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenGL_GL_PREFERENCE GLVND)

add_subdirectory(thirdParty)

find_package(OpenGL REQUIRED)

file(
    GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

project("2DComputerGraphics" VERSION 0.1)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    imgui PUBLIC
    SDL3::SDL3
    OpenGL::OpenGL
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    cxxopts_interface
    SDL3::SDL3
    imgui
    OpenGL::OpenGL
)
