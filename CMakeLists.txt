cmake_minimum_required(VERSION "3.12")
project("GeoTile" LANGUAGES CXX)

include("GoogleTest")

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

option(ENABLE_GEOTILETESTS "Builds the GeoTile GoogleTest suite." ON)

add_library("${PROJECT_NAME}"
  "src/point.cpp"
  "src/tile.cpp"
  "include/GeoTile/meta.hpp"
  "include/GeoTile/point.hpp"
  "include/GeoTile/tile.hpp"
)

target_include_directories("${PROJECT_NAME}" PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_compile_options("${PROJECT_NAME}" PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall
    -Wextra
    -Werror
    -pedantic-errors
  >
)

target_compile_features("${PROJECT_NAME}" PUBLIC
  "cxx_std_17"
)

set_target_properties("${PROJECT_NAME}" PROPERTIES
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
  INTERPROCEDURAL_OPTIMIZATION ON
  INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF
)

if (ENABLE_GEOTILETESTS)
  enable_testing()

  set(TEST_PROJECT_NAME "${PROJECT_NAME}_tests")
  set(GTEST_PROJECT_LIB "gtest")

  add_executable("${TEST_PROJECT_NAME}"
    "tests/src/main.cpp"
    "tests/src/point.cpp"
    "tests/src/tile.cpp"
  )

  target_link_libraries("${TEST_PROJECT_NAME}" PRIVATE
      "${PROJECT_NAME}"
      "${GTEST_PROJECT_LIB}"
  )

  target_compile_options("${TEST_PROJECT_NAME}" PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
      -Wall
      -Wextra
      -Werror
      -pedantic-errors
    >
  )

  target_compile_features("${TEST_PROJECT_NAME}" PUBLIC
    "cxx_std_17"
  )

  set_target_properties("${TEST_PROJECT_NAME}" PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    INTERPROCEDURAL_OPTIMIZATION ON
    INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF
  )

  set(BUILD_GMOCK OFF CACHE INTERNAL "")
  set(INSTALL_GTEST OFF CACHE INTERNAL "")

  add_subdirectory("tests/thirdparty/googletest")

  target_compile_features("${GTEST_PROJECT_LIB}" PUBLIC
    "cxx_std_17"
  )

  set_target_properties("${GTEST_PROJECT_LIB}" PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    INTERPROCEDURAL_OPTIMIZATION ON
    INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF
  )

  gtest_discover_tests("${TEST_PROJECT_NAME}")
endif()
