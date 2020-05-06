#ifndef LIBGEOTILE_POINT_HPP_
#define LIBGEOTILE_POINT_HPP_

#include <tuple>

struct Point
{
    static Point fromLatLon(double latitude, double longitude);
    static Point fromPixel(int pixelX, int pixelY, int zoom);
    static Point fromMeters(double meterX, double meterY);
    double getLatitude();
    double getLongitude();

private:
    Point(double latitude, double longitude);
    double latitude_;
    double longitude_;
    static std::tuple<int, int> signMeters(double meterX, double meterY, int pixelX, int pixelY, int zoom);
};

#endif

