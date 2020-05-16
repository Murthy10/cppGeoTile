#ifndef LIBGEOTILE_TILE_HPP_
#define LIBGEOTILE_TILE_HPP_

#include "point.hpp"

#include <tuple>
#include <string>

struct Tile
{
    static Tile fromMeters(double meterX, double meterY);
    static Tile fromTms(int tmsX, int tmsY, unsigned int zoom);
    static Tile fromGoogle(int googleX, int googleY, unsigned int zoom);
    static Tile fromQuadTree(std::string);
    static Tile forLatLon(double latitude, double longitude, unsigned int zoom);
    static Tile forPoint(Point point, unsigned int zoom);
    static Tile forPixels(int pixelX, int pixelY, unsigned int zoom);
    static Tile forMeters(double meterX, double meterY, unsigned int zoom);
    std::tuple<Point, Point> bounds();
    std::tuple<int, int> getTms();
    std::tuple<int, int> getGoogle();
    std::string getQuadTree();
    int getZoom();

private:
    Tile(int tmsX, int tmsY, unsigned int zoom);
    int tmsX_;
    int tmsY_;
    unsigned int zoom_;
};

#endif
