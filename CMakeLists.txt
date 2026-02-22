cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cxxopts_interface INTERFACE)

file(
    GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

project("2DComputerGraphics")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(
    cxxopts_interface
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/cxxopts
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        cxxopts_interface
)
