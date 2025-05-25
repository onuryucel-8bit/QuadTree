cmake_minimum_required(VERSION 3.28.2)
project(QuadTree)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SDL3_INCLUDE_DIR "D:/Libs/SDL3-3.2.12/include")
set(SDL3_LIBRARY "D:/Libs/SDL3-3.2.12/lib/x64/SDL3.lib")

add_executable(QuadTree 
    Source.cpp 
    DSA/QuadTree.cpp 
    Math/Rectangle.cpp)

target_include_directories(QuadTree PRIVATE 
    ${SDL3_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/DSA 
    ${CMAKE_SOURCE_DIR}/Math
)

target_link_libraries(QuadTree PRIVATE ${SDL3_LIBRARY}  )
