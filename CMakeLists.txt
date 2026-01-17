cmake_minimum_required(VERSION 3.14)
project(TheGame)

set(PROJECT_NAME TheGame)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window/gamewindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texture/gametexture.cpp
)

set(
    INC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/window
    ${CMAKE_CURRENT_SOURCE_DIR}/include/exception
    ${CMAKE_CURRENT_SOURCE_DIR}/include/texture
    ${CMAKE_CURRENT_SOURCE_DIR}/include/utility
)

include(FetchContent)
#add_compile_options(-arch arm64)


FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.0
)

FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
    SDL3_Image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-3.2.6
)

FetchContent_MakeAvailable(SDL3_Image)

add_executable(
    ${PROJECT_NAME}
    ${SRCS}
)

include_directories(
    ${INC}
)

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE 
    SDL3::SDL3
    SDL3_image::SDL3_image
)