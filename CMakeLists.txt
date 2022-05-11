cmake_minimum_required(VERSION 3.14.0)
project(Circle_Bezier VERSION 2.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(ImGui-SFML REQUIRED)

add_executable(Circle 
    circle.cpp
)
target_include_directories(Circle PRIVATE ${SFML_INCLUDE_DIR} ${ImGui-SFML_DIR})

target_link_libraries(Circle sfml-graphics ImGui-SFML::ImGui-SFML)

add_executable(Bezier 
    bezier.cpp
)
target_include_directories(Bezier PRIVATE ${SFML_INCLUDE_DIR} ${ImGui-SFML_DIR})

target_link_libraries(Bezier sfml-graphics ImGui-SFML::ImGui-SFML)

add_executable(Transform 
    transform.cpp
)
target_include_directories(Transform PRIVATE ${SFML_INCLUDE_DIR} ${ImGui-SFML_DIR})

target_link_libraries(Transform sfml-graphics ImGui-SFML::ImGui-SFML)


# Make .exe (Windows)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(BUILD_FOR_WIN TRUE)
endif()

option(STATIC_BUILD "Build a static binary." ${BUILD_FOR_WIN})

if (STATIC_BUILD)
        set(CMAKE_EXE_LINKER_FLAGS "-static")
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
        set(BUILD_SHARED_LIBS OFF)
endif()
