cmake_minimum_required(VERSION 3.10)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# set the project name
project(cppGeoTile)

configure_file(cppGeoTileConfig.h.in cppGeoTileConfig.h)

add_subdirectory(libs)
add_subdirectory(app)

