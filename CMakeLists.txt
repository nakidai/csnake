cmake_minimum_required(VERSION 3.5)
project(csnake VERSION 1.1 LANGUAGES C)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed.")
endif()

add_executable(csnake
  src/main.c
  src/screen.c
  src/input.c
  src/player.c
  src/sleep.c
  src/platform/getch.c
  src/platform/game.c
)

set_target_properties(csnake PROPERTIES C_STANDARD 11)
set_target_properties(csnake PROPERTIES C_EXTENSIONS FALSE)
if(${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
    target_link_libraries(csnake pthread)
endif()
target_include_directories(csnake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SIZE 10 CACHE STRING "Size of game field")
set(DEFX 0 CACHE STRING "Start x")
set(DEFY 0 CACHE STRING "Start y")
set(SLEEP 1000 CACHE STRING "Sleep between frames (ms)")

configure_file(include/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h)
