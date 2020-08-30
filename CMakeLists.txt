cmake_minimum_required(VERSION 3.17)
project(trains)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(trains
        file_reader.cc
        main.cc Graph.cc Graph.h Vertex.cc Vertex.h)
