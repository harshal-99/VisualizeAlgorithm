cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
project(VisualizeAlgorithm)
include(CMake/StandardProjectSettings.cmake)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" ON)
    if(ENABLED_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(VisualizeAlgorithm -ftime-trace)
    endif()
endif()

include(CMake/Cache.cmake)

include(CMake/CompilerWarnings.cmake)

include(CMake/Sanatizers.cmake)
enable_sanitizers(VisualizeAlgorithm)

include(CMake/Doxygen.cmake)
enable_doxygen()

include(CMake/Sanatizers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraires" OFF)

add_executable(main src/main src/renderAlgo.cpp include/renderAlgo.hpp)

target_link_libraries(main ${SFML_LIBRIES} -lGL -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio)


