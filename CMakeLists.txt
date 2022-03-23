cmake_minimum_required(VERSION 3.15)
project(shortestpaths_pogil)

set(CMAKE_CXX_STANDARD 20)

add_executable(shortestpaths_pogil main.cpp graph.cpp graph.h vertex.cpp vertex.h colours.h example_graphs.cpp example_graphs.h shortest_path_data.cpp shortest_path_data.h dfs_traversal.cpp dfs_traversal.h shortest_paths.cpp shortest_paths.h shortest_paths_tester.cpp shortest_paths_tester.h heap_data.cpp heap_data.h)

target_compile_options(shortestpaths_pogil PRIVATE -Wall -Wextra -pedantic)
