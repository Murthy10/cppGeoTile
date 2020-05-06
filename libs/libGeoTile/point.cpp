#include <math.h>
#include <tuple>

#include "point.h"
#include "meta.h"

inline Point::Point(double latitude, double longitude) : latitude_(latitude), longitude_(longitude){};

inline Point Point::fromPixel(int pixelX, int pixelY, int zoom)
{
    auto maxPixel = pow(2, zoom) * TILE_SIZE;
    auto meterX = pixelX * resolution(zoom) - ORIGIN_SHIFT;
    auto meterY = pixelY * resolution(zoom) - ORIGIN_SHIFT;
    auto signedMeters = signMeters(meterX, meterY, pixelX, pixelY, zoom);
    return Point::fromMeters(std::get<0>(signedMeters), std::get<1>(signedMeters));
}
inline Point Point::fromMeters(double meterX, double meterY)
{
    auto longitude = (meterX / ORIGIN_SHIFT) * 180.0;
    auto latitude = (meterY / ORIGIN_SHIFT) * 180.0;
    latitude = 180.0 / M_PI * (2 * atan(exp(latitude * M_PI / 180.0)) - M_PI / 2.0);
    return Point(latitude, longitude);
}

inline std::tuple<int, int> Point::signMeters(double meterX, double meterY, int pixelX, int pixelY, int zoom)
{
    auto halfSize = int((TILE_SIZE * pow(2, zoom)) / 2);
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
    return std::make_tuple(meterX, meterY);
}

inline double Point::getLatitude()
{
    return latitude_;
}
inline double Point::getLongitude()
{
    return longitude_;
}