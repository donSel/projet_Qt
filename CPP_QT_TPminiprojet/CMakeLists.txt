cmake_minimum_required(VERSION 3.10)
project(CPP_QT_TPminiprojet)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG REQUIRED)

file (GLOB_RECURSE sourceCode src/*.cpp src/*.h)

add_executable(CPP_QT_TPminiprojet ${sourceCode} src/Player.cpp src/Player.h src/WindowTwo.cpp src/WindowTwo.h)

target_link_libraries(CPP_QT_TPminiprojet Qt5::Widgets)