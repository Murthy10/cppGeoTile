cmake_minimum_required(VERSION 3.10)
project(GeoTile LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  SET(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
endif()

add_library(${PROJECT_NAME} SHARED
  src/meta.cpp
  src/point.cpp
  src/tile.cpp
)

add_library(libs::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(
  "${PROJECT_NAME}"
  PUBLIC
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:Gnu>>:
    -Wall
    -Wextra
    -Werror
    -pedantic-errors
  >
)

