cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
project(VisualizeAlgorithm)

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