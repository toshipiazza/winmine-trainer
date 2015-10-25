cmake_minimum_required(VERSION 2.8)
project(msweep_trainer)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions("-std=c++11")
endif()

add_executable(trainer trainer.cpp inject.h inject.cpp)

add_library(get_layout SHARED get_layout.cpp)
add_library(mines_visible SHARED mines_visible.cpp)
add_library(freeze_timer SHARED freeze_timer.cpp)
add_library(disable_mines SHARED disable_mines.cpp)
add_library(auto_win SHARED auto_win.cpp)

install(FILES winmine.exe DESTINATION ${CMAKE_CURRENT_BINARY_DIR})