const auto EARTH_RADIUS = 6378137.0;
const auto TILE_SIZE = 256;
const auto ORIGIN_SHIFT = 2.0 * M_PI * EARTH_RADIUS / 2.0;
const auto INITIAL_RESOLUTION = 2.0 * M_PI * EARTH_RADIUS / TILE_SIZE;

double resolution(int zoom);