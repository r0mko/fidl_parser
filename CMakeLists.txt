cmake_minimum_required(VERSION 2.8)

project(spirit_parser)
add_definitions( -DBOOST_SPIRIT_USE_PHOENIX_V3=1 )
file( GLOB SRC_FILES src/* )
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${SRC_FILES})
