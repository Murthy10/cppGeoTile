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

  set(BUILD_GMOCK OFF CACHE INTERNAL "")
  set(INSTALL_GTEST OFF CACHE INTERNAL "")

  add_subdirectory("tests/thirdparty/googletest")

  add_executable("${PROJECT_NAME}_tests"
    "tests/src/main.cpp"
    "tests/src/point.cpp"
    "tests/src/tile.cpp"
  )

  target_link_libraries("${PROJECT_NAME}_tests" PRIVATE
      "${PROJECT_NAME}"
      "gtest"
  )

  target_compile_options("${PROJECT_NAME}_tests" PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
      -Wall
      -Wextra
      -Werror
      -pedantic-errors
    >
  )

  gtest_discover_tests("${PROJECT_NAME}_tests")
endif()
