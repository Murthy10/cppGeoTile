cmake_minimum_required(VERSION 3.10)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# set the project name
project(cppGeoTile)

configure_file(cppGeoTileConfig.h.in cppGeoTileConfig.h)

# add own library
add_subdirectory(./include/libGeoTile)


# add the executable
add_executable(cppGeoTile ./src/main.cpp)

target_link_libraries(cppGeoTile PUBLIC ./include/libGeoTile)

target_include_directories(cppGeoTile PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/include/libGeoTile"
                           )

