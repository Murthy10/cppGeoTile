#include "point.hpp"

#include <iostream>

int main()
{
    auto point = Point::fromLatLon(47.0, 8.0);
    std::cout << point.getLatitude() << "\n";
}
