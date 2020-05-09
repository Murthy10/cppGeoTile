#include <gtest/gtest.h>

#include "point.hpp"

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
    auto latLon = getChicagoLatLon();
    auto lat = std::get<0>(latLon);
    auto lon = std::get<1>(latLon);

    auto meters = getChicagoMeters();
    auto meterX = std::get<0>(meters);
    auto meterY = std::get<1>(meters);

    auto point = Point::fromMeters(meterX, meterY);
    auto resultingMeters = point.getMeters();

    ASSERT_NEAR(std::get<0>(resultingMeters), meterX, 0.1);
    ASSERT_NEAR(std::get<1>(resultingMeters), meterY, 0.1);

    ASSERT_NEAR(point.getLatitude(), lat, 0.1);
    ASSERT_NEAR(point.getLongitude(), lon, 0.1);
}

TEST(point, fromPixel)
{
    auto latLon = getChicagoLatLon();
    auto lat = std::get<0>(latLon);
    auto lon = std::get<1>(latLon);

    auto zoom = 19;
    auto pixel = getChicagoPixel();
    auto pixelX = std::get<0>(pixel);
    auto pixelY = std::get<1>(pixel);

    auto point = Point::fromPixel(pixelX, pixelY, zoom);
    auto resultingPixel = point.getPixels(zoom);

    ASSERT_NEAR(std::get<0>(resultingPixel), pixelX, 5);
    ASSERT_NEAR(std::get<1>(resultingPixel), pixelY, 5);

    ASSERT_NEAR(point.getLatitude(), lat, 0.1);
    ASSERT_NEAR(point.getLongitude(), lon, 0.1);
}

TEST(point, pixelToMeters)
{
    auto meters = getChicagoMeters();
    auto meterX = std::get<0>(meters);
    auto meterY = std::get<1>(meters);

    auto zoom = 19;
    auto pixel = getChicagoPixel();
    auto pixelX = std::get<0>(pixel);
    auto pixelY = std::get<1>(pixel);

    auto point = Point::fromPixel(pixelX, pixelY, zoom);
    auto resultingMeters = point.getMeters();

    ASSERT_NEAR(std::get<0>(resultingMeters), meterX, 20);
    ASSERT_NEAR(std::get<1>(resultingMeters), meterY, 20);

    auto resultingPixel = point.getPixels(zoom);
    ASSERT_NEAR(std::get<0>(resultingPixel), pixelX, 5);
    ASSERT_NEAR(std::get<1>(resultingPixel), pixelY, 5);
}

TEST(point, metersToPixel)
{
    auto meters = getChicagoMeters();
    auto meterX = std::get<0>(meters);
    auto meterY = std::get<1>(meters);

    auto zoom = 19;
    auto pixel = getChicagoPixel();
    auto pixelX = std::get<0>(pixel);
    auto pixelY = std::get<1>(pixel);

    auto point = Point::fromMeters(meterX, meterY);
    auto resultingMeters = point.getMeters();

    ASSERT_NEAR(std::get<0>(resultingMeters), meterX, 100);
    ASSERT_NEAR(std::get<1>(resultingMeters), meterY, 100);

    auto resultingPixel = point.getPixels(zoom);
    ASSERT_NEAR(std::get<0>(resultingPixel), pixelX, 100);
    ASSERT_NEAR(std::get<1>(resultingPixel), pixelY, 100);
}