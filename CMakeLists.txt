cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("2DComputerGraphics" VERSION 0.1)

add_subdirectory(vendors)
add_subdirectory(core)

file(
    GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    cxxopts_interface
    SDL3::SDL3
    SDL3_image::SDL3_image
    imgui
    core
)
