#include "point.hpp"
#include "meta.hpp"

#include <cmath>

Point::Point(double latitude, double longitude) : latitude_(latitude), longitude_(longitude){};

Point Point::fromPixel(int pixelX, int pixelY, unsigned int zoom)
{
    // unused: auto maxPixel = 1 << zoom * TILE_SIZE;
    auto meterX = pixelX * resolution(zoom) - ORIGIN_SHIFT;
    auto meterY = pixelY * resolution(zoom) - ORIGIN_SHIFT;
    auto [x, y] = signMeters(meterX, meterY, pixelX, pixelY, zoom);
    return Point::fromMeters(x, y);
}

Point Point::fromMeters(double meterX, double meterY)
{
    auto longitude = (meterX / ORIGIN_SHIFT) * 180.0;
    auto latitude = (meterY / ORIGIN_SHIFT) * 180.0;
    latitude = 180.0 / M_PI * (2 * atan(exp(latitude * M_PI / 180.0)) - M_PI / 2.0);
    return Point(latitude, longitude);
}

Point Point::fromLatLon(double latitude, double longitude)
{
    return Point{latitude, longitude};
}

std::tuple<int, int> Point::signMeters(double meterX, double meterY, int pixelX, int pixelY, unsigned int zoom)
{
    auto halfSize = TILE_SIZE * (1 << zoom) / 2;
    meterX = std::abs(meterX);
    meterY = std::abs(meterY);
    if (pixelX < halfSize)
    {
        meterX *= -1;
    }
    if (pixelY > halfSize)
    {
        meterY *= -1;
    }
    return {meterX, meterY};
}

double Point::getLatitude()
{
    return latitude_;
}

double Point::getLongitude()
{
    return longitude_;
}

std::tuple<double, double> Point::getLatLon()
{
    return {latitude_, longitude_};
}

std::tuple<double, double> Point::getMeters()
{
    auto meterX = longitude_ * ORIGIN_SHIFT / 180.0;
    auto meterY = std::log(std::tan((90.0 + latitude_) * M_PI / 360.0)) / (M_PI / 180.0);
    return {meterX, meterY * ORIGIN_SHIFT / 180.0};
}

std::tuple<int, int> Point::getPixels(unsigned int zoom)
{
    auto [meterX, meterY] = getMeters();
    auto pixelX = (meterX + ORIGIN_SHIFT) / resolution(zoom);
    auto pixelY = (meterY - ORIGIN_SHIFT) / resolution(zoom);
    return {std::abs(std::round(pixelX)), std::abs(std::round(pixelY))};
}
