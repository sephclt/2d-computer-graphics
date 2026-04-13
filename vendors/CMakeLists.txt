add_library(cxxopts_interface INTERFACE)

target_include_directories(
    cxxopts_interface INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/cxxopts
)

add_subdirectory(sdl3 EXCLUDE_FROM_ALL)
add_subdirectory(sdl_image EXCLUDE_FROM_ALL)
add_subdirectory(imgui)
