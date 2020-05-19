cmake_minimum_required(VERSION "3.12")
project("GeoTile"
  LANGUAGES CXX
  VERSION "1.0.0"
  HOMEPAGE_URL "https://github.com/Murthy10/cppGeoTile"
  DESCRIPTION "C++ library to handle tiles and points of different projections, in particular WGS 84 (Latitude, Longitude), Spherical Mercator (Meters), Pixel Pyramid and Tiles (TMS, Google, QuadTree)"
)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

option(ENABLE_GEOTILETESTS "Builds the GeoTile GoogleTest suite." NO)

### Main Library

set("${PROJECT_NAME}_HEADERS"
  "include/GeoTile/meta.hpp"
  "include/GeoTile/point.hpp"
  "include/GeoTile/tile.hpp"
)

add_library("${PROJECT_NAME}"
  "src/point.cpp"
  "src/tile.cpp"
  ${${PROJECT_NAME}_HEADERS}
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
  PUBLIC_HEADER "${${PROJECT_NAME}_HEADERS}"
)

include("CMakePackageConfigHelpers")

install(TARGETS "${PROJECT_NAME}"
  EXPORT "${PROJECT_NAME}Targets"
  PUBLIC_HEADER DESTINATION "include/GeoTile"
)

write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    COMPATIBILITY "AnyNewerVersion"
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
)

install(FILES
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  DESTINATION "lib/cmake/${PROJECT_NAME}"
)

install(EXPORT "${PROJECT_NAME}Targets"
  DESTINATION "lib/cmake/${PROJECT_NAME}"
  NAMESPACE "${PROJECT_NAME}::"
)

### Unit Tests

if (ENABLE_GEOTILETESTS)
  enable_testing()
  include("GoogleTest")
  find_package("GTest" REQUIRED)

  set(TEST_PROJECT_NAME "${PROJECT_NAME}_tests")

  add_executable("${TEST_PROJECT_NAME}"
    "tests/src/point.cpp"
    "tests/src/tile.cpp"
  )

  target_link_libraries("${TEST_PROJECT_NAME}" PRIVATE
      "${PROJECT_NAME}"
      "GTest::GTest"
      "GTest::Main"
  )

  target_compile_options("${TEST_PROJECT_NAME}" PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
      -Wall
      -Wextra
      -Werror
      -pedantic-errors
    >
  )

  set_target_properties("${TEST_PROJECT_NAME}" PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    INTERPROCEDURAL_OPTIMIZATION ON
  )

  gtest_discover_tests("${TEST_PROJECT_NAME}")
endif()
