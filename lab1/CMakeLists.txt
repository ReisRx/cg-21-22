cmake_minimum_required(VERSION 3.14)

project(TestOpenGL CXX)

add_executable(Lab2 src/lab2.cpp)
add_executable(Lab3 src/lab3.cpp)
# add_executable(MyName src/name.cpp)
# add_executable(Square src/square.cpp)
# add_executable(Pentagon src/pentagon.cpp)

add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)


target_include_directories(Lab2 PUBLIC extern/glad/include
    PUBLIC extern/glfw/include)
target_include_directories(Lab3 PUBLIC extern/glad/include
    PUBLIC extern/glfw/include)
# target_include_directories(MyName PUBLIC extern/glad/include
#     PUBLIC extern/glfw/include)
# target_include_directories(Square PUBLIC extern/glad/include
#     PUBLIC extern/glfw/include)
# target_include_directories(Pentagon PUBLIC extern/glad/include
#     PUBLIC extern/glfw/include)


target_link_directories(Lab2 PUBLIC extern/glad/src
    PUBLIC extern/glfw/src)
target_link_directories(Lab3 PUBLIC extern/glad/src
    PUBLIC extern/glfw/src)
# target_link_directories(MyName PUBLIC extern/glad/src
#     PUBLIC extern/glfw/src)
# target_link_directories(Square PUBLIC extern/glad/src
#     PUBLIC extern/glfw/src)
# target_link_directories(Pentagon PUBLIC extern/glad/src
#     PUBLIC extern/glfw/src)


target_link_libraries(Lab2 PRIVATE glad
    PRIVATE glfw)
target_link_libraries(Lab3 PRIVATE glad
    PRIVATE glfw)
# target_link_libraries(MyName PRIVATE glad
#     PRIVATE glfw)
# target_link_libraries(Square PRIVATE glad
#     PRIVATE glfw)
# target_link_libraries(Pentagon PRIVATE glad
#     PRIVATE glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)