cmake_minimum_required(VERSION 3.8.0)

set(project_name remote_driving)  

project(${project_name})

set(INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/lib)

include_directories("${INCLUDE_DIR}")

# file(GLOB_RECURSE srcs "src/*.cpp")

add_executable(driving_server src/main.cpp)

function(SetDefaultTargetProperties target)
    set_target_properties(${target} PROPERTIES CXX_STANDARD 11)
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../run)
endfunction()

SetDefaultTargetProperties(driving_server)

target_link_libraries(driving_server ${LIB_DIR}/libhpsocket.so.5)
target_link_libraries(driving_server ${LIB_DIR}/libSSD.so pthread)
