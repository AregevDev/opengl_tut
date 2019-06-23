cmake_minimum_required(VERSION 3.14)
project(opengl_tut)

set(CMAKE_CXX_STANDARD 17)

if (MSVC OR MINGW)
	set(VCPKG_PATH C:/Users/AregevDev/.vcpkg)
	set(TARGET_OS x64-windows-static)
elseif (UNIX AND NOT APPLE)
	set(VCPKG_PATH ~/vcpkg)
	set(TARGET_OS x64-linux)	
endif ()

set(CMAKE_TOOLCHAIN_FILE ${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake)
set(glfw3_DIR ${VCPKG_PATH}/installed/x64-windows-static/share/glfw3)
set(glad_DIR ${VCPKG_PATH}/installed/${TARGET_OS}/share/glad)
set(glm_DIR ${VCPKG_PATH}/installed/${TARGET_OS}/share/glm)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(opengl src/main.cpp src/vertexbuffer.cpp src/vertexbuffer.h src/indexbuffer.cpp src/indexbuffer.h src/vertexarray.h src/vertexbufferlayout.h src/vertexarray.cpp src/vertexbufferlayout.cpp src/shader.cpp src/shader.h)

configure_file(${CMAKE_SOURCE_DIR}/shaders/triangle.glsl ${PROJECT_BINARY_DIR}/shaders/triangle.glsl COPYONLY)

target_link_libraries(opengl PRIVATE glfw glad::glad glm)
