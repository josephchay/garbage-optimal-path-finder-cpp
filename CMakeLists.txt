cmake_minimum_required(VERSION 3.26)
project(program_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(program_files
        src/maps/MapMatrix.h
        src/maps/GarbageLocations.h
        src/routes/GreedyRoute.h
        src/maps/Locations.h
        main.cpp
        src/routes/NonOptimizedRoute.h
        src/routes/OptimizedRoute.h
        src/routes/TSPRoute.h
        src/maps/wasteLevel.h
        utils/Converter.h
        src/metrics/Metrics.h
        src/filesystem/FileReader.cpp
        src/authentication/Login.cpp
        src/authentication/Participant.cpp
        src/collection/validator/InputValidator.cpp
        src/collection/validator/InputValidator.h
        src/collection/InputCollector.cpp
        src/utils/Datetime.cpp
        src/utils/Structures.cpp
        data/Config.cpp
        src/filesystem/FileWriter.h)
