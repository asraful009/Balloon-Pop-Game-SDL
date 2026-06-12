cmake_minimum_required(VERSION 3.16)
project(PopDrop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(PopDrop
    main.cpp
    private/Window.cpp
    private/Balloon.cpp
)

target_include_directories(PopDrop PRIVATE
    ${CMAKE_SOURCE_DIR}/public
)

target_link_libraries(PopDrop PRIVATE
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
)

set_target_properties(PopDrop PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)