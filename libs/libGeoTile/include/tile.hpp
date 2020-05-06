#ifndef LIBGEOTILE_TILE_HPP_
#define LIBGEOTILE_TILE_HPP_

#include "point.hpp"

struct Tile
{
    static Tile fromLatLon(double latitude, double longitude, int zoom);
    static Tile fromPixel(int pixelX, int pixelY, int zoom);
    static Tile fromMeters(double meterX, double meterY);
    static Tile fromTms(int tmsX, int tmsY, int zoom);
    static Tile fromGoogle(int googleX, int googleY, int zoom);
    static Tile fromPoint(Point point, int zoom);
    double getLatitude();
    double getLongitude();

private:
    Tile(double latitude, double longitude, int zoom);
    double tmsX_;
    double tmsY_;
    int zoom_;
};

#endif

