#include "point.hpp"
#include "meta.hpp"

Point::Point(double latitude, double longitude) : latitude_(latitude), longitude_(longitude){};

Point Point::fromPixel(int pixelX, int pixelY, int zoom)
{
    auto maxPixel = std::pow(2, zoom) * TILE_SIZE;
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

Point Point::fromLatLon(double, double) {
    // TODO: Implement
    return Point { 0, 0 };
}

std::tuple<int, int> Point::signMeters(double meterX, double meterY, int pixelX, int pixelY, int zoom)
{
    auto halfSize = static_cast<int>((TILE_SIZE * std::pow(2, zoom)) / 2);
    meterX = abs(meterX);
    meterY = abs(meterY);
    if (pixelX < halfSize)
    {
        meterX *= -1;
    }
    if (pixelY > halfSize)
    {
        meterY *= -1;
    }
    return { meterX, meterY };
}

double Point::getLatitude()
{
    return latitude_;
}

double Point::getLongitude()
{
    return longitude_;
}

