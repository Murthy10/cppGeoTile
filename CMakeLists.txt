cmake_minimum_required(VERSION 3.10)
project(cppGeoTile LANGUAGES CXX)

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

configure_file(cppGeoTileConfig.h.in cppGeoTileConfig.h)

add_subdirectory(libs/libGeoTile)
add_subdirectory(app)
