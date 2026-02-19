cmake_minimum_required(VERSION 3.28)
project(space_invaders)

set(BUILD_SHARED_LIBS OFF)
set(SDL3_DIR libs/SDL3-3.4.0/cmake/)
set(SDL3_image_DIR libs/SDL3_image-3.4.0/cmake)
set(SDL3_ttf_DIR libs/SDL3_ttf-3.2.2/cmake)
set(CMAKE_C_FLAGS " -Wnarrowing ")
set(CMAKE_CXX_STANDARD 17)

# Link statico per runtime GCC
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED)
add_library(easy_sdl src/easy_sdl.cpp
        examples/hello_edl.cpp)
target_link_libraries(easy_sdl
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf-shared
        SDL3_image::SDL3_image-shared
)

add_executable(hello_edl
        examples/hello_edl.cpp
        src/easy_sdl.cpp
)

target_link_libraries(hello_edl
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image-shared
)
