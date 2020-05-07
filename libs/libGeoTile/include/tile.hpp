#ifndef LIBGEOTILE_TILE_HPP_
#define LIBGEOTILE_TILE_HPP_

#include "point.hpp"

struct Tile
{
    static Tile fromMeters(double meterX, double meterY);
    static Tile fromTms(int tmsX, int tmsY, int zoom);
    static Tile fromGoogle(int googleX, int googleY, int zoom);
    static Tile forLatLon(double latitude, double longitude, int zoom);
    static Tile forPoint(Point point, int zoom);
    static Tile forPixels(int pixelX, int pixelY, int zoom);
    static Tile forMeters(double meterX, double meterY, int zoom);
    std::tuple<int, int> getTms();
    std::tuple<int, int> getGoogle();
    int getZoom();

private:
    Tile(int tmsX, int tmsY, int zoom);
    int tmsX_;
    int tmsY_;
    int zoom_;
};

#endif

