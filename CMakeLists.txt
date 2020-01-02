cmake_minimum_required(VERSION 3.0)

# set the project name
project(Chess)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(pieces src/Pieces.cpp)
target_include_directories(pieces
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_library(board src/Board.cpp)
target_include_directories(board
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(board pieces)

# add the executable
add_executable(chess src/main.cpp)
target_link_libraries(chess board pieces)
target_include_directories(chess PUBLIC include)
