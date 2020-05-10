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

if (NOT ENABLE_TESTING)
  set(ENABLE_TESTING ON)
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  SET(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
endif()

set(HEADERS
  "include/GeoTile/meta.hpp"
  "include/GeoTile/point.hpp"
  "include/GeoTile/tile.hpp"
)

set(SOURCES
  "src/point.cpp"
  "src/tile.cpp"
)

add_library("${PROJECT_NAME}" SHARED
  "${SOURCES}"
  "${HEADERS}"
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
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall
    -Wextra
    -Werror
    -pedantic-errors
  >
)

if (ENABLE_TESTING)
  include(cmake/googletest.cmake)
  fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
  )
  
  enable_testing()

  set(TEST_PROJECT_NAME "${PROJECT_NAME}_unit_tests")

  add_executable(
    "${TEST_PROJECT_NAME}"
    "tests/main.cpp"
    "tests/point.cpp"
    "tests/tile.cpp"
  )

  target_link_libraries(
      "${TEST_PROJECT_NAME}"
      "gtest"
      "libs::GeoTile"
  )

  target_compile_options(
    "${TEST_PROJECT_NAME}"
    PUBLIC
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
      -Wall
      -Wextra
      -Werror
      -pedantic-errors
    >
  )

  add_test(
    NAME
      "unit"
    COMMAND
      "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests"
  )
endif()
