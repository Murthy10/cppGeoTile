#include "tile.hpp"
#include "meta.hpp"
#include "point.hpp"

Tile::Tile(int tmsX, int tmsY, int zoom) : tmsX_(tmsX), tmsY_(tmsX), zoom_(zoom){};

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

int Tile::getZoom()
{
    return zoom_;
}