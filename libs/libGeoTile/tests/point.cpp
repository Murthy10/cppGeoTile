#include "GeoTile/point.hpp"

#include <gtest/gtest.h>

#include <tuple>

std::tuple<double, double> getChicagoMeters()
{
    return {-9757148.442088600, 5138517.444985110};
}

std::tuple<double, double> getChicagoLatLon()
{
    return {41.85, -87.65};
}

std::tuple<int, int> getChicagoPixel()
{
    return {34430575, 49899071};
}

TEST(point, fromLatLon)
{
    auto latitude = 47.0;
    auto longitude = 8.0;
    auto point = Point::fromLatLon(latitude, longitude);
    ASSERT_DOUBLE_EQ(point.getLatitude(), latitude);
    ASSERT_DOUBLE_EQ(point.getLongitude(), longitude);
}

TEST(point, fromMeters)
{
    auto [lat, lon] = getChicagoLatLon();

    auto [meterX, meterY] = getChicagoMeters();

    auto point = Point::fromMeters(meterX, meterY);
    auto [resultX, resultY] = point.getMeters();

    ASSERT_NEAR(resultX, meterX, 0.1);
    ASSERT_NEAR(resultY, meterY, 0.1);

    ASSERT_NEAR(point.getLatitude(), lat, 0.1);
    ASSERT_NEAR(point.getLongitude(), lon, 0.1);
}

TEST(point, fromPixel)
{
    auto [lat, lon] = getChicagoLatLon();

    auto zoom = 19;
    auto [pixelX, pixelY] = getChicagoPixel();

    auto point = Point::fromPixel(pixelX, pixelY, zoom);
    auto [resultX, resultY] = point.getPixels(zoom);

    ASSERT_NEAR(resultX, pixelX, 5);
    ASSERT_NEAR(resultY, pixelY, 5);

    ASSERT_NEAR(point.getLatitude(), lat, 0.1);
    ASSERT_NEAR(point.getLongitude(), lon, 0.1);
}

TEST(point, pixelToMeters)
{
    auto meters = getChicagoMeters();
    auto meterX = std::get<0>(meters);
    auto meterY = std::get<1>(meters);

    auto zoom = 19;
    auto [pixelX, pixelY] = getChicagoPixel();

    auto point = Point::fromPixel(pixelX, pixelY, zoom);
    auto [resultMeterX, resultMeterY] = point.getMeters();

    ASSERT_NEAR(resultMeterX, meterX, 20);
    ASSERT_NEAR(resultMeterY, meterY, 20);

    auto [resultPixelX, resultPixelY] = point.getPixels(zoom);
    ASSERT_NEAR(resultPixelX, pixelX, 5);
    ASSERT_NEAR(resultPixelY, pixelY, 5);
}

TEST(point, metersToPixel)
{
    auto [meterX, meterY] = getChicagoMeters();

    auto zoom = 19;
    auto [pixelX, pixelY] = getChicagoPixel();

    auto point = Point::fromMeters(meterX, meterY);
    auto [resultMeterX, resultMeterY] = point.getMeters();

    ASSERT_NEAR(resultMeterX, meterX, 100);
    ASSERT_NEAR(resultMeterY, meterY, 100);

    auto [resultPixelX, resultPixelY] = point.getPixels(zoom);
    ASSERT_NEAR(resultPixelX, pixelX, 100);
    ASSERT_NEAR(resultPixelY, pixelY, 100);
}
