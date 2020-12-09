#include "GeoTile/tile.hpp"
#include "GeoTile/meta.hpp"
#include "GeoTile/point.hpp"

#include <algorithm>
#include <sstream>
#include <iterator>
#include <numeric>
#include <vector>
#include <utility>

Tile::Tile(int tmsX, int tmsY, unsigned int zoom) : tmsX_(tmsX), tmsY_(tmsY), zoom_(zoom) {}

Tile Tile::fromQuadTree(std::string quadTree)
{
    int zoom = quadTree.size();
    auto offset = (1 << zoom) - 1;

    std::vector<int> digits{};
    transform(cbegin(quadTree), cend(quadTree), back_inserter(digits), [](auto c) {
        return c - '0';
    });

    auto [googleX, googleY] = accumulate(cbegin(digits), cend(digits), std::pair{0, 0}, [](auto acc, auto digit) {
        auto quotient = digit / 2;
        auto remainder = digit % 2;
        return std::pair{(acc.first << 1) | remainder, (acc.second << 1) | quotient};
    });

    int tmsY = offset - googleY;
    return Tile::fromTms(googleX, tmsY, zoom);
}

Tile Tile::fromTms(int tmsX, int tmsY, unsigned int zoom)
{
    return {tmsX, tmsY, zoom};
}

Tile Tile::fromGoogle(int googleX, int googleY, unsigned int zoom)
{
    int tmsY = (1 << zoom) - 1 - googleY;
    return Tile::fromTms(googleX, tmsY, zoom);
}

Tile Tile::forPixels(int pixelX, int pixelY, unsigned int zoom)
{
    auto tmsX = static_cast<int>(std::ceil(pixelX / static_cast<double>(TILE_SIZE)) - 1);
    auto tmsY = static_cast<int>(std::ceil(pixelY / static_cast<double>(TILE_SIZE)) - 1);
    tmsY = (1 << zoom) - 1 - tmsY;
    return Tile::fromTms(tmsX, tmsY, zoom);
}

Tile Tile::forLatLon(double latitude, double longitude, unsigned int zoom)
{
    auto point = Point::fromLatLon(latitude, longitude);
    auto [pixelX, pixelY] = point.getPixels(zoom);
    return Tile::forPixels(pixelX, pixelY, zoom);
}

Tile Tile::forPoint(Point point, unsigned int zoom)
{
    return Tile::forLatLon(point.getLatitude(), point.getLongitude(), zoom);
}

Tile Tile::forMeters(double meterX, double meterY, unsigned int zoom)
{
    auto point = Point::fromMeters(meterX, meterY);
    auto [pixelX, pixelY] = point.getPixels(zoom);
    return Tile::forPixels(pixelX, pixelY, zoom);
}

std::tuple<int, int> Tile::getTms()
{
    return {tmsX_, tmsY_};
}

std::tuple<int, int> Tile::getGoogle()
{
    auto googleY = (1 << zoom_) - 1 - tmsY_;
    return {tmsX_, googleY};
}

std::string Tile::getQuadTree()
{
    int tmsX = tmsX_;
    int tmsY = (1 << zoom_) - 1 - tmsY_;

    std::stringstream strStream;
   
    for(int i = zoom_; i > 0; i--){
        auto digit = 0;
        auto maks = 1 << (i - 1);
        if ((tmsX & maks) != 0)
        {
            digit += 1;
        }
        if ((tmsY & maks) != 0)
        {
            digit += 2;
        }
        strStream << digit;
    }
    return strStream.str();
}

int Tile::getZoom()
{
    return zoom_;
}

std::tuple<Point, Point> Tile::bounds()
{
    auto [googleX, googleY] = getGoogle();

    auto pixelXWest = googleX * TILE_SIZE;
    auto pixelYNorth = googleY * TILE_SIZE;

    auto pixelXEast = (googleX + 1) * TILE_SIZE;
    auto pixelYSouth = (googleY + 1) * TILE_SIZE;

    auto pointMin = Point::fromPixel(pixelXWest, pixelYSouth, zoom_);
    auto pointMax = Point::fromPixel(pixelXEast, pixelYNorth, zoom_);
    return {pointMin, pointMax};
}
