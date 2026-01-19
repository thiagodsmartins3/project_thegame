cmake_minimum_required(VERSION 3.14)
project(DebugLogger)

set(PROJECT_NAME DebugLogger)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BIN_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(
    SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/debuglogger/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/debuglogger/logger.cpp
)

set(
    INC
    ${CMAKE_CURRENT_SOURCE_DIR}/debuglogger/logger.hpp
)

add_executable(
    ${PROJECT_NAME}
    ${SRCS}
)

include_directories(
    ${INC}
)