cmake_minimum_required(VERSION 3.27)
project(Hack_a_duck)

set(CMAKE_CXX_STANDARD 14)

set(LIBPATH "C:/Libs/")

include_directories(${PROJECT_NAME}
        "${LIBPATH}SDL2-2.28.5/include"
        "${LIBPATH}SDL2_image-2.8.2/include"
        "${LIBPATH}SDL2_ttf-2.20.2/include"
)

add_executable(Hack_a_duck
        src/main.cpp)

target_link_libraries(${PROJECT_NAME}
        "${LIBPATH}SDL2-2.28.5/lib/x64/SDL2.lib"
        "${LIBPATH}SDL2_image-2.8.2/lib/x64/SDL2_image.lib"
        "${LIBPATH}SDL2_ttf-2.20.2/lib/x64/SDL2_ttf.lib"
)