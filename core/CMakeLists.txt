add_library(
    core STATIC
    src/core.cxx
    src/core_draw.cxx
    src/core_file.cxx
    src/core_log.cxx
)

target_include_directories(
    core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(
    core PUBLIC cxx_std_23
)

target_link_libraries(
    core PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    imgui
)
