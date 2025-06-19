cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

project(Sonic)
set(CMAKE_CXX_STANDARD 17)


set(VK_SDK_PATH $ENV{VK_SDK_PATH})
message(${VK_SDK_PATH})

file(GLOB_RECURSE source_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_files} ${include_files})

add_library(Sonic STATIC ${source_files} ${include_files})
target_precompile_headers(Sonic PRIVATE "src/pch.h")
target_link_directories(Sonic PUBLIC ${VK_SDK_PATH}/Lib)

target_include_directories(Sonic PUBLIC 
	${VK_SDK_PATH}/Include
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/src/Core
	${CMAKE_CURRENT_SOURCE_DIR}/src/Vulkan)

target_link_libraries(Sonic PUBLIC ${VK_SDK_PATH}/Lib/vulkan-1.lib)

add_subdirectory(vendor/glfw)
target_link_libraries(Sonic PUBLIC glfw)
