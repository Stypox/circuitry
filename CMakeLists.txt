cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

#Enable debug symbols
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 20)

project(circuitry)

# imported libraries
add_library(lSOIL STATIC IMPORTED)
add_library(lstdc++fs STATIC IMPORTED)
add_library(lGL STATIC IMPORTED)
add_library(lGLU STATIC IMPORTED)
add_library(lglfw3 STATIC IMPORTED)
add_library(lX11 STATIC IMPORTED)
add_library(lXxf86vm STATIC IMPORTED)
add_library(lXrandr STATIC IMPORTED)
add_library(lpthread STATIC IMPORTED)
add_library(lXi STATIC IMPORTED)
add_library(ldl STATIC IMPORTED)
add_library(lXinerama STATIC IMPORTED)
add_library(lXcursor STATIC IMPORTED)

# project libraries
file(GLOB_RECURSE GL_ABSTRACTIONS_SOURCES libs/gl-abstractions/*.cpp)
add_library(gl-abstractions OBJECT ${GL_ABSTRACTIONS_SOURCES})
target_include_directories(gl-abstractions PRIVATE libs/glad/include)
add_library(glad OBJECT libs/glad/src/glad.c)
target_include_directories(glad PRIVATE libs/glad/include)

#Add the files
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(executable ${SOURCES} $<TARGET_OBJECTS:gl-abstractions> $<TARGET_OBJECTS:glad>)
target_link_libraries(executable SOIL stdc++fs GL GLU glfw3 X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor)

# Includes
target_include_directories(executable PRIVATE src)
target_include_directories(executable PRIVATE libs/stock-container/include)
target_include_directories(executable PRIVATE libs/glad/include)
target_include_directories(executable PRIVATE libs/gl-abstractions/include)
