#include <iostream>
#include <string>
#include <math.h>
#include <tuple>

using namespace std;

// const auto PI = 3.14159265358979323846;
const auto PI = M_PI;
const auto EARTH_RADIUS = 6378137.0;
const auto TILE_SIZE = 256;
const auto ORIGIN_SHIFT = 2.0 * PI * EARTH_RADIUS / 2.0;
const auto INITIAL_RESOLUTION = 2.0 * PI * EARTH_RADIUS / TILE_SIZE;

// auto pow(int base, int exponent)
// {
//     if (exponent == 0)
//     {
//         return 1;
//     }
//     auto result = base;
//     for (int i = 1; i < exponent; i++)
//     {
//         result *= base;
//     }
//     return result;
// }

auto resolution(int zoom)
{
    return INITIAL_RESOLUTION / pow(2, zoom);
}

class Point
{
public:
    static Point fromLatLon(float latitude, float longitude);
    static Point fromPixel(int pixelX, int pixelY, int zoom);
    static Point fromMeters(float meterX, float meterY);

private:
    Point(float latitude, float longitude);
    float latitude_;
    float longitude_;
    static std::tuple<int, int> signMeters(float meterX, float meterY, int pixelX, int pixelY, int zoom);
};

inline Point::Point(float latitude, float longitude) : latitude_(latitude), longitude_(longitude){};

inline Point Point::fromPixel(int pixelX, int pixelY, int zoom)
{
    auto maxPixel = pow(2, zoom) * TILE_SIZE;
    auto meterX = pixelX * resolution(zoom) - ORIGIN_SHIFT;
    auto meterY = pixelY * resolution(zoom) - ORIGIN_SHIFT;
    auto signedMeters = signMeters(meterX, meterY, pixelX, pixelY, zoom);
    return Point::fromMeters(std::get<0>(signedMeters), std::get<1>(signedMeters));
}
inline Point Point::fromMeters(float meterX, float meterY)
{
    auto longitude = (meterX / ORIGIN_SHIFT) * 180.0;
    auto latitude = (meterY / ORIGIN_SHIFT) * 180.0;
    latitude = 180.0 / PI * (2 * atan(exp(latitude * PI / 180.0)) - PI / 2.0);
    return Point(latitude, longitude);
}

inline std::tuple<int, int> Point::signMeters(float meterX, float meterY, int pixelX, int pixelY, int zoom)
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

int main()
{
    auto result = pow(2, 10);

    cout << result << " ";
    cout << endl;
}