cmake_minimum_required(VERSION 3.5)
project(csnake VERSION 0.1.0 LANGUAGES C)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed.")
endif()

add_executable(csnake
  src/main.c
  src/screen.c
  src/input.c
  src/player.c
)

set_target_properties(csnake PROPERTIES C_STANDARD 11)
set_target_properties(csnake PROPERTIES C_EXTENSIONS FALSE)
target_include_directories(csnake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SIZE 10 CACHE STRING "Size of game field")
set(DEFX 0 CACHE STRING "Start x")
set(DEFY 0 CACHE STRING "Start y")

configure_file(include/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h)
