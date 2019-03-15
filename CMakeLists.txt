cmake_minimum_required(VERSION 2.8)
project(spirit_parser)

if (UNIX)
    set(BOOST_ROOT "/opt/local/include")
    add_definitions(-D__UNIX__)
endif (UNIX)

find_package (Boost 1.65 REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_definitions( -DBOOST_SPIRIT_USE_PHOENIX_V3=1)

file( GLOB SRC_FILES src/* )
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${SRC_FILES})
