#include <gtest/gtest.h>

#include "tile.hpp"
#include "point.hpp"

int zoom()
{
    return 7;
}

std::tuple<int, int> google()
{
    return {67, 44};
}

std::tuple<int, int> tms()
{
    return {67, 83};
}

std::string quadTree()
{
    return "1202211";
}

TEST(tile, fromTms)
{
    auto [tmsX, tmsY] = tms();

    auto tile = Tile::fromTms(tmsX, tmsY, zoom());

    auto [resultingTmsX, resultingTmsY] = tile.getTms();

    ASSERT_EQ(resultingTmsX, tmsX);
    ASSERT_EQ(resultingTmsY, tmsY);
}

TEST(tile, fromGoogle)
{
    auto [googleX, googleY] = google();

    auto tile = Tile::fromGoogle(googleX, googleY, zoom());

    auto [tmsX, tmsY] = tms();
    auto [resultingTmsX, resultingTmsY] = tile.getTms();

    ASSERT_EQ(resultingTmsX, tmsX);
    ASSERT_EQ(resultingTmsY, tmsY);
}

TEST(tile, fromQuadTree)
{
    auto tile = Tile::fromQuadTree(quadTree());

    auto [tmsX, tmsY] = tms();
    auto [resultingTmsX, resultingTmsY] = tile.getTms();

    ASSERT_EQ(resultingTmsX, tmsX);
    ASSERT_EQ(resultingTmsY, tmsY);
    ASSERT_EQ(tile.getZoom(), zoom());
}

TEST(tile, crossCheck)
{
    auto tile = Tile::fromQuadTree(quadTree());

    auto [tmsX, tmsY] = tms();
    auto [googleX, googleY] = google();

    auto [resultingTmsX, resultingTmsY] = tile.getTms();
    auto [resultingGoogleX, resultingGoogleY] = tile.getGoogle();

    ASSERT_EQ(resultingTmsX, tmsX);
    ASSERT_EQ(resultingTmsY, tmsY);
    ASSERT_EQ(resultingGoogleX, googleX);
    ASSERT_EQ(resultingGoogleY, googleY);
    ASSERT_EQ(tile.getQuadTree(), quadTree());
    ASSERT_EQ(tile.getZoom(), zoom());
}

int zoomChicago()
{
    return 19;
}

std::tuple<double, double> chicagoMeters()
{
    return {-9757148.442088600, 5138517.444985110};
}

std::tuple<double, double> chicagoLatLon()
{
    return {41.85, -87.65};
}

std::tuple<int, int> chicagoPixel()
{
    return {34430575, 49899071};
}

std::tuple<int, int> chicagoTms()
{
    return {134494, 329369};
}

std::string chicagoQuadTree()
{
    return "0302222310303211330";
}

TEST(tile, forPixel)
{
    auto [pixelX, pixelY] = chicagoPixel();
    auto tile = Tile::forPixels(pixelX, pixelY, zoomChicago());

    auto [tmsX, tmsY] = chicagoTms();
    auto [resultingTmsX, resultingTmsY] = tile.getTms();

    ASSERT_NEAR(resultingTmsX, tmsX, 2);
    ASSERT_NEAR(resultingTmsY, tmsY, 2);
    ASSERT_EQ(tile.getZoom(), zoomChicago());
}

TEST(tile, forMeters)
{
    auto [meterX, meterY] = chicagoMeters();
    auto tile = Tile::forMeters(meterX, meterY, zoomChicago());

    auto [tmsX, tmsY] = chicagoTms();
    auto [resultingTmsX, resultingTmsY] = tile.getTms();

    ASSERT_NEAR(resultingTmsX, tmsX, 2);
    ASSERT_NEAR(resultingTmsY, tmsY, 2);
    ASSERT_EQ(tile.getZoom(), zoomChicago());
}

TEST(tile, forLatLon)
{
    auto [lat, lon] = chicagoLatLon();
    auto tile = Tile::forLatLon(lat, lon, zoomChicago());

    auto [tmsX, tmsY] = chicagoTms();
    auto [resultingTmsX, resultingTmsY] = tile.getTms();

    ASSERT_NEAR(resultingTmsX, tmsX, 2);
    ASSERT_NEAR(resultingTmsY, tmsY, 2);
    ASSERT_EQ(tile.getZoom(), zoomChicago());
}

TEST(tile, forPoint)
{
    auto [lat, lon] = chicagoLatLon();
    auto point = Point::fromLatLon(lat, lon);
    auto tile = Tile::forPoint(point, zoomChicago());

    auto [tmsX, tmsY] = chicagoTms();
    auto [resultingTmsX, resultingTmsY] = tile.getTms();

    ASSERT_NEAR(resultingTmsX, tmsX, 2);
    ASSERT_NEAR(resultingTmsY, tmsY, 2);
    ASSERT_EQ(tile.getZoom(), zoomChicago());
}

TEST(tile, bounds)
{
    auto tile = Tile::fromQuadTree(chicagoQuadTree());
    int pixelMinBoundX = 34430464;
    int pixelMinBoundY = 49899264;

    int pixelMaxBoundX = 34430720;
    int pixelMaxBoundY = 49899008;

    auto [pointMin, pointMax] = tile.bounds();

    auto [resultingMinX, resultingMinY] = pointMin.getPixels(tile.getZoom());
    auto [resultingMaxX, resultingMaxY] = pointMax.getPixels(tile.getZoom());

    ASSERT_NEAR(resultingMinX, pixelMinBoundX, 2);
    ASSERT_NEAR(resultingMinY, pixelMinBoundY, 2);
    ASSERT_NEAR(resultingMaxX, pixelMaxBoundX, 2);
    ASSERT_NEAR(resultingMaxY, pixelMaxBoundY, 2);
}