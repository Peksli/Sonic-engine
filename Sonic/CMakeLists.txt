cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

project(Sonic)

file(GLOB_RECURSE source_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_files} ${include_files})

add_library(Sonic STATIC ${source_files} ${include_files})

target_include_directories(Sonic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Sonic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Core)