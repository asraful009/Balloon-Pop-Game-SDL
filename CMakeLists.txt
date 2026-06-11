cmake_minimum_required(VERSION 3.16)
project(t3)

set(CMAKE_CXX_STANDARD 17)

# static linking
set(SDL2_STATIC ON)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(t3
    main.cpp
    private/Window.cpp
    private/Balloon.cpp
)

# Add include path
target_include_directories(t3 PRIVATE ${CMAKE_SOURCE_DIR}/public)

target_link_libraries(t3 PRIVATE 
    SDL2::SDL2-static
    SDL2_ttf::SDL2_ttf-static
    SDL2_image::SDL2_image-static
)