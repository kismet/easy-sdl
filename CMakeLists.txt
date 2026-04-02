cmake_minimum_required(VERSION 3.28)
project(easy_sdl)

set(BUILD_SHARED_LIBS OFF)
set(SDL3_DIR libs/SDL3-3.4.0/cmake)
set(SDL3_mixer_DIR libs/SDL3_mixer-3.2.0/cmake)
set(SDL3_image_DIR libs/SDL3_image-3.4.0/cmake)
set(SDL3_ttf_DIR libs/SDL3_ttf-3.2.2/cmake)
set(CMAKE_CXX_STANDARD 17)

# Link statico per runtime GCC
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)

add_library(easy_sdl src/easy_sdl.cpp
        examples/basic/hello_edl.cpp)

target_link_libraries(easy_sdl
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf-shared
        SDL3_image::SDL3_image-shared
        SDL3_mixer::SDL3_mixer-shared
)

add_executable(hello_edl
        examples/basic/hello_edl.cpp
        src/easy_sdl.cpp
)

add_executable(hello_audio
        examples/basic/hello_audio.cpp
        src/easy_sdl.cpp
)

add_executable(hello_image
        examples/basic/hello_image.cpp
        src/easy_sdl.cpp
)

add_executable(hello_text
        examples/basic/hello_text.cpp
        src/easy_sdl.cpp
)

add_executable(hello_text_multiline
        examples/text/hello_text_multiline.cpp
        src/easy_sdl.cpp
)

add_executable(hello_text_complex
        examples/text/hello_text_complex.cpp
        src/easy_sdl.cpp
)

add_executable(hello_avatar
        examples/event/hello_avatar.cpp
        src/easy_sdl.cpp
)

add_executable(hello_avatar_moving
        examples/event/hello_avatar_moving.cpp
        src/easy_sdl.cpp
)

add_executable(hello_text_fps
        examples/text/hello_text_fps.cpp
        src/easy_sdl.cpp
)

target_link_libraries(hello_edl
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image-shared
)

target_link_libraries(hello_audio
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image-shared
        SDL3_mixer::SDL3_mixer-shared
)


target_link_libraries(hello_image
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image-shared
)

target_link_libraries(hello_text
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image-shared
)

target_link_libraries(hello_text_multiline
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image-shared
)


target_link_libraries(hello_text_complex
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image-shared
)

target_link_libraries(hello_avatar
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image-shared
)

target_link_libraries(hello_avatar_moving
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image-shared
)

target_link_libraries(hello_text_fps
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image-shared
)
