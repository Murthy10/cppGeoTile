#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

#include "tile.hpp"
#include "meta.hpp"
#include "point.hpp"

Tile::Tile(int tmsX, int tmsY, int zoom) : tmsX_(tmsX), tmsY_(tmsY), zoom_(zoom){};

Tile Tile::fromQuadTree(std::string quadTree)
{
    int zoom = quadTree.size();
    auto offset = pow(2, zoom) - 1;

    std::vector<int> digits;
    std::for_each(quadTree.begin(), quadTree.end(), [&digits](char c) {
        int digit = c - '0';
        digits.push_back(digit);
    });

    int googleX = 0;
    int googleY = 0;
    for (auto digit : digits)
    {
        int quotient = (int)digit / 2;
        int remainder = digit % 2;
        googleX = (googleX << 1) | remainder;
        googleY = (googleY << 1) | quotient;
    }

    char quadTreeChars[quadTree.size()];
    quadTree.copy(quadTreeChars, quadTree.size());

    int tmsY = offset - googleY;
    return Tile::fromTms(googleX, tmsY, zoom);
}

Tile Tile::fromTms(int tmsX, int tmsY, int zoom)
{
    return Tile{tmsX, tmsY, zoom};
}

Tile Tile::fromGoogle(int googleX, int googleY, int zoom)
{
    int tmsY = pow(2, zoom - 1) - googleY;
    return Tile::fromTms(googleX, tmsY, zoom);
}

Tile Tile::forPixels(int pixelX, int pixelY, int zoom)
{
    auto tmsX = static_cast<int>(ceil(pixelX / TILE_SIZE) - 1);
    auto tmsY = static_cast<int>(ceil(pixelY / TILE_SIZE) - 1);
    tmsY = pow(2, zoom - 1) - tmsY;
    return Tile::fromTms(tmsX, tmsY, zoom);
}

Tile Tile::forLatLon(double latitude, double longitude, int zoom)
{
    auto point = Point::fromLatLon(latitude, longitude);
    auto pixels = point.getPixels(zoom);
    auto pixelX = std::get<0>(pixels);
    auto pixelY = std::get<1>(pixels);
    return Tile::forPixels(pixelX, pixelY, zoom);
}

Tile Tile::forPoint(Point point, int zoom)
{
    return Tile::forLatLon(point.getLatitude(), point.getLongitude(), zoom = zoom);
}

Tile Tile::forMeters(double meterX, double meterY, int zoom)
{
    auto point = Point::fromMeters(meterX, meterY);
    auto pixels = point.getPixels(zoom);
    auto pixelX = std::get<0>(pixels);
    auto pixelY = std::get<1>(pixels);
    return Tile::forPixels(pixelX, pixelY, zoom);
}

std::tuple<int, int> Tile::getTms()
{
    return {tmsX_, tmsY_};
}

std::tuple<int, int> Tile::getGoogle()
{
    auto googleY = pow(2, zoom_ - 1) - tmsY_;
    return {tmsX_, googleY};
}

std::string Tile::getQuadTree()
{
    int tmsX = tmsX_;
    int tmsY = pow(2, zoom_ - 1) - tmsY_;
    std::vector<int> digits;
    for (int i = zoom_; i > 0; i--)
    {
        int digit = 0;
        auto maks = 1 << (i - 1);
        if ((tmsX & maks) != 0)
        {
            digit += 1;
        }
        if ((tmsY & maks) != 0)
        {
            digit += 2;
        }
        if (digit == 3)
        {
            digit %= 2;
        }
        digits.push_back(digit);
    }
    std::stringstream strStream;
    copy(digits.begin(), digits.end(), std::ostream_iterator<int>(strStream, ""));
    return strStream.str();
}

int Tile::getZoom()
{
    return zoom_;
}