cmake_minimum_required(VERSION 2.8)
project(spirit_parser)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX)
    set(BOOST_ROOT "/opt/local/include")
    add_definitions(-D__UNIX__)
endif (UNIX)

find_package (Boost 1.65 REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
include_directories(src/)
file(GLOB ADASIS_FILES
  "deploy/*"
)
file(COPY ${ADASIS_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_definitions( -DBOOST_SPIRIT_USE_PHOENIX_V3=1)

file(GLOB_RECURSE SRCS src/*.cpp)
file(GLOB_RECURSE HDRS src/*.h)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRCS} ${HDRS})


