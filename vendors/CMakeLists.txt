add_library(cxxopts_interface INTERFACE)

target_include_directories(
    cxxopts_interface INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/cxxopts
)

add_subdirectory(sdl3)
add_subdirectory(sdl_image)
add_subdirectory(imgui)
