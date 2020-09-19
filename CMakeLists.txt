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




add_executable(BubbleSort BubbleSort.cpp commonHeader.hpp)
add_executable(CombSort CombSort.cpp commonHeader.hpp)
add_executable(HeapSort HeapSort.cpp commonHeader.hpp)
add_executable(QuickSort QuickSort.cpp commonHeader.hpp)
add_executable(RadixSort RadixSort.cpp commonHeader.hpp)
add_executable(SelectionSort SelectionSort+BubbleSort.cpp commonHeader.hpp)
add_executable(ShellSort ShellSort.cpp commonHeader.hpp)
add_executable(ALL BubbleSort.cpp CombSort.cpp
        HeapSort.cpp
        QuickSort.cpp
        RadixSort.cpp
        SelectionSort+BubbleSort.cpp
        ShellSort.cpp commonHeader.hpp)

include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(BubbleSort ${SDL2_LIBRAIES} -lSDL2)
target_link_libraries(CombSort ${SDL2_LIBRAIES} -lSDL2)
target_link_libraries(HeapSort ${SDL2_LIBRAIES} -lSDL2)
target_link_libraries(QuickSort ${SDL2_LIBRAIES} -lSDL2)
target_link_libraries(RadixSort ${SDL2_LIBRAIES} -lSDL2)
target_link_libraries(SelectionSort ${SDL2_LIBRAIES} -lSDL2)
target_link_libraries(ShellSort ${SDL2_LIBRAIES} -lSDL2)
target_link_libraries(ALL ${SDL2_LIBRAIES} -lSDL2)