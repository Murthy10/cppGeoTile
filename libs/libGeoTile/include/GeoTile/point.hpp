#ifndef LIBGEOTILE_POINT_HPP_
#define LIBGEOTILE_POINT_HPP_

#include <tuple>

struct Point
{
    static Point fromLatLon(double latitude, double longitude);
    static Point fromPixel(int pixelX, int pixelY, unsigned int zoom);
    static Point fromMeters(double meterX, double meterY);
    std::tuple<double, double> getLatLon();
    std::tuple<double, double> getMeters();
    std::tuple<int, int> getPixels(unsigned int zoom);
    double getLatitude();
    double getLongitude();

private:
    Point(double latitude, double longitude);
    double latitude_;
    double longitude_;
    static std::tuple<int, int> signMeters(double meterX, double meterY, int pixelX, int pixelY, unsigned int zoom);
};

#endif
