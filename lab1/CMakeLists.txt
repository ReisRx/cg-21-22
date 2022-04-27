cmake_minimum_required(VERSION 3.14)

project(TestOpenGL VERSION 0.1.1
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall)

add_executable(Lab2 "src/lab2/lab2.cpp" "src/glad.c")
add_executable(Lab3 "src/lab3/lab3.cpp" "src/glad.c")
add_executable(Lab4 "src/lab4/lab4.cpp" "src/glad.c" "src/stb_image.cpp")
add_executable(Lab5 "src/lab5/lab5.cpp" "src/glad.c" "src/stb_image.cpp")

target_include_directories(Lab2 PUBLIC "libs/include")
target_include_directories(Lab3 PUBLIC "libs/include")
target_include_directories(Lab4 PUBLIC "libs/include")
target_include_directories(Lab5 PUBLIC "libs/include")

target_link_directories(Lab2 PRIVATE "libs/lib")
target_link_directories(Lab3 PRIVATE "libs/lib")
target_link_directories(Lab4 PRIVATE "libs/lib")
target_link_directories(Lab5 PRIVATE "libs/lib")

find_package(assimp REQUIRED)

target_link_libraries(Lab2 PRIVATE glfw3)
target_link_libraries(Lab3 PRIVATE glfw3)
target_link_libraries(Lab4 PRIVATE glfw3 assimp)
target_link_libraries(Lab5 PRIVATE glfw3)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)