cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(pcltyre_proj)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (pcltyre_proj PCLTest1.cpp)
target_link_libraries (pcltyre_proj ${PCL_LIBRARIES})
 

