cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
project(VisualizeAlgorithm)

add_executable(BubbleSort BubbleSort.cpp)
add_executable(CombSort CombSort.cpp)
add_executable(HeapSort HeapSort.cpp)
add_executable(QuickSort QuickSort.cpp)
add_executable(RadixSort RadixSort.cpp)
add_executable(SelectionSort SelectionSort+BubbleSort.cpp)
add_executable(ShellSort ShellSort.cpp)
