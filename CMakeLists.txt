cmake_minimum_required(VERSION 3.14)
project(opengl_tut)

set(CMAKE_CXX_STANDARD 17)

add_executable(opengl src/main.cpp src/vertexbuffer.cpp src/vertexbuffer.h src/indexbuffer.cpp src/indexbuffer.h src/vertexarray.h src/vertexbufferlayout.h src/vertexarray.cpp src/vertexbufferlayout.cpp)
target_include_directories(opengl PRIVATE C:\\users\\AregevDev\\.libs\\include)
target_link_directories(opengl PRIVATE C:\\users\\AregevDev\\.libs\\lib)

configure_file(${CMAKE_SOURCE_DIR}/shaders/triangle_v.glsl ${PROJECT_BINARY_DIR}/shaders/triangle_v.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/shaders/triangle_f.glsl ${PROJECT_BINARY_DIR}/shaders/triangle_f.glsl COPYONLY)

if (UNIX AND NOT APPLE)
    set_target_properties(opengl PROPERTIES OUTPUT_NAME opengl.out)
    target_link_libraries(opengl glfw3 glad GL X11 m pthread dl rt)
endif ()

target_link_libraries(opengl glfw3 glad)
