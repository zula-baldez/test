cmake_minimum_required(VERSION 3.24)
project(yadro)

set(CMAKE_CXX_STANDARD 20)
add_executable(yadro main.cpp tape/TapeImpl.cpp tape-sort/TapeSortMergeImpl.cpp)
enable_testing()
add_subdirectory(tests)
