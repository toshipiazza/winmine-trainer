cmake_minimum_required(VERSION 2.8)
project(msweep_trainer)

find_library(PSAPI Psapi)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions("-std=c++11")
endif()

add_executable(trainer trainer.cpp inject.h inject.cpp)
target_link_libraries(trainer ${PSAPI})

add_library(get_layout SHARED get_layout.cpp common_globals.h)
add_library(mines_visible SHARED mines_visible.cpp common_globals.h)
add_library(freeze_timer SHARED freeze_timer.cpp common_globals.h)
add_library(disable_mines SHARED disable_mines.cpp common_globals.h)
add_library(auto_win SHARED auto_win.cpp common_globals.h)

install(FILES winmine.exe DESTINATION ${CMAKE_BINARY_DIR})
