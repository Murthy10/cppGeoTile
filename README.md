# cppGeoTile

C++ library to handle tiles and points of different projections, in particular WGS 84 (Latitude, Longitude), Spherical Mercator (Meters), Pixel Pyramid and Tiles (TMS, Google, QuadTree)

## Usage

The library cppGeoTile consist of two main classes, namely Point and Tile.
As already mentioned they allow you to convert various geo projections.

### Point

Example of the class Point.

```cpp
#include <iostream>

#include <GeoTile/point.hpp>

int main(int argc, char **argv)
{
    // meters in Spherical Mercator EPSG:900913
    auto zoom = 19;
    auto meterX = -9757148.442088600;
    auto meterY = 5138517.444985110;

    auto point = Point::fromMeters(meterX, meterY);

    auto [pixelX, pixelY] = point.getPixels(zoom);
    std::cout << "PixelX: " << pixelX << "PixelY: " << pixelY << "\n";

    auto [lat, lon] = point.getLatLon();
    std::cout << "Latitude: " << lat << "Longitude: " << lon << "\n";
}
```

### Tile

Example of the class Tile.

```cpp
#include <iostream>

#include <GeoTile/tile.hpp>

int main(int argc, char **argv)
{
    auto zoom = 19;
    auto tmsX = 134494;
    auto tmsY = 329369;

    auto tile = Tile::fromTms(tmsX, tmsY, zoom); // Tile Map Service (TMS) X Y and zoom

    std::cout << "QuadTree: " << tile.getQuadTree()<< "\n"; // QuadTree: 0302222310303211330
    std::cout << "Google: " << tile.getGoogle()<< "\n"; // Google:  (134494, 194918)
}
```

## Installation
Configure: `cmake -S . -B build`

Additional configuration options:

- `-DCMAKE_BUILD_TYPE=Release` to enable optimizations. (Default: `Debug`)
- `-DENABLE_GEOTILETEST=OFF` to disable building the tests. (Default `ON`)

Build: `cmake --build build`

Run tests: `./build/tests/GeoTileTest`

## Notes

This repository is a C++ port of (my) [pyGeoTile](https://github.com/geometalab/pyGeoTile).

Further, it is inspired by:

- Tiles à la Google Maps: http://www.maptiler.org/google-maps-coordinates-tile-bounds-projection/
- Bing Maps Tile System: https://msdn.microsoft.com/en-us/library/bb259689.aspx
- Showing pixel and tile coordinates: https://developers.google.com/maps/documentation/javascript/examples/map-coordinates?hl=de
- Mercantile: https://github.com/mapbox/mercantile
