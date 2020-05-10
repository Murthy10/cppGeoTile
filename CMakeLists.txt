cmake_minimum_required(VERSION 3.12)
project(GeoTile LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

option(ENABLE_TESTING "Builds the GoogleTest test suite." ON)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  SET(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
endif()

set(
  HEADERS
  "include/GeoTile/meta.hpp"
  "include/GeoTile/point.hpp"
  "include/GeoTile/tile.hpp"
)

set(
  SOURCES
  "src/point.cpp"
  "src/tile.cpp"
)

add_library(
  "${PROJECT_NAME}"
  SHARED
  "${SOURCES}"
  "${HEADERS}"
)

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
  enable_testing()

  add_subdirectory("tests/thirdparty/googletest")

  set(BUILD_GMOCK OFF)
  set(INSTALL_GTEST OFF)

  set(
    TEST_PROJECT_NAME
    "${PROJECT_NAME}_unit_tests"
  )

  add_executable(
    "${TEST_PROJECT_NAME}"
    "tests/main.cpp"
    "tests/point.cpp"
    "tests/tile.cpp"
  )

  target_link_libraries(
      "${TEST_PROJECT_NAME}"
      PRIVATE
      "${PROJECT_NAME}"
      "gtest"
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
endif()
