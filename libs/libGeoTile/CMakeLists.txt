project(libGeoTile)

add_library(${PROJECT_NAME} SHARED
	meta.cpp
	point.cpp
	tile.cpp
)

add_library(libs::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)