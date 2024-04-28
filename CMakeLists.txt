cmake_minimum_required(VERSION 3.26)
project(program_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(program_files
        MapMatrix.h
        GarbageLocations.h
        GreedyRoute.h
        Locations.h
        main.cpp
        NonOptimizedRoute.h
        OptimizedRoute.h
        TSPRoute.h
        wasteLevel.h
        utils/Converter.h)
