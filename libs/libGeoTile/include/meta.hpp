#ifndef LIBGEOTILE_META_HPP_
#define LIBGEOTILE_META_HPP_

#include <cmath>

constexpr auto EARTH_RADIUS = 6378137.0;
constexpr auto TILE_SIZE = 256;
constexpr auto ORIGIN_SHIFT = 2.0 * M_PI * EARTH_RADIUS / 2.0;
constexpr auto INITIAL_RESOLUTION = 2.0 * M_PI * EARTH_RADIUS / TILE_SIZE;

double resolution(int zoom);

#endif

