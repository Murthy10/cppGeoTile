#include <gtest/gtest.h>

#include "point.hpp"

TEST(point, fromLatLon)
{
    auto point = Point::fromLatLon(47.0, 8.0);
    ASSERT_DOUBLE_EQ(point.getLatitude(), 47.0);
}