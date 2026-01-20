cmake_minimum_required(VERSION 3.14)
project(TheGame)

set(PROJECT_NAME TheGame)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


set(BIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(
    SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window/gamewindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texture/gametexture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/gameaudio.cpp
)

set(
    INC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/window
    ${CMAKE_CURRENT_SOURCE_DIR}/include/exception
    ${CMAKE_CURRENT_SOURCE_DIR}/include/texture
    ${CMAKE_CURRENT_SOURCE_DIR}/include/utility
    ${CMAKE_CURRENT_SOURCE_DIR}/include/audio
)

set(LOGGER ${CMAKE_CURRENT_SOURCE_DIR}/utility)

include(FetchContent)

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

FetchContent_Declare(
    portaudio
    GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
    GIT_TAG master 
)

FetchContent_MakeAvailable(portaudio)

FetchContent_Declare(
    libsndfile
    GIT_REPOSITORY https://github.com/libsndfile/libsndfile.git
    GIT_TAG master
)

FetchContent_MakeAvailable(libsndfile)

add_compile_definitions(DEBUG)

add_subdirectory(${LOGGER})

add_executable(
    ${PROJECT_NAME}
    ${SRCS}
)

add_custom_command(
    TARGET TheGame
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
        ${BIN_PATH} 
    COMMENT "Copying executable to bin folder"
)

 include_directories(
    ${INC}
)

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE 
    SDL3::SDL3
    SDL3_image::SDL3_image
    portaudio
    sndfile
)