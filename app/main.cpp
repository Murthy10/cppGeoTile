#include <iostream>
#include <string>
#include <math.h>
#include <tuple>

#include <libGeoTile/point.h>

int main()
{
    auto point = Point::fromLatLon(47.0, 8.0);
    std::cout << point.getLatitude() << " ";
    std::cout << std::endl;
}