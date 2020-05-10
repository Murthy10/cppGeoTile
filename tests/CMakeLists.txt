cmake_minimum_required(VERSION 3.12)
project(GeoTileTest LANGUAGES CXX)

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

set(BUILD_GMOCK OFF CACHE INTERNAL "")
set(INSTALL_GTEST OFF CACHE INTERNAL "")

add_subdirectory("thirdparty/googletest")

set(
  SOURCES
  "src/main.cpp"
  "src/point.cpp"
  "src/tile.cpp"
)

add_executable(
  "${PROJECT_NAME}"
  "${SOURCES}"
)

target_link_libraries(
    "${PROJECT_NAME}"
    PRIVATE
    "GeoTile"
    "gtest"
)

target_compile_options(
  "${PROJECT_NAME}"
  PUBLIC
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall
    -Wextra
    -Werror
    -pedantic-errors
  >
)
