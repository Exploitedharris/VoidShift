cmake_minimum_required(VERSION 3.10)
project(VoidShift)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(VoidShift src/main.cpp src/Game.cpp)
target_link_libraries(VoidShift sfml-graphics sfml-window sfml-system)
