# cppGeoTile

C++ library to handle tiles and points of different projections, in particular WGS 84 (Latitude, Longitude), Spherical Mercator (Meters), Pixel Pyramid and Tiles (TMS, Google, QuadTree)

## Usage

The library cppGeoTile consist of two main classes, namely Point and Tile.
As already mentioned they allow you to convert various geo projections.

### Point

Example of the class Point.

```cpp
#include <GeoTile/point.hpp>

#include <iostream>

int main()
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
#include <GeoTile/tile.hpp>

#include <iostream>

int main()
{
    auto zoom = 19;
    auto tmsX = 134494;
    auto tmsY = 329369;

    auto tile = Tile::fromTms(tmsX, tmsY, zoom); // Tile Map Service (TMS) X Y and zoom

    std::cout << "QuadTree: " << tile.getQuadTree()<< "\n"; // QuadTree: 0302222310303211330
    std::cout << "Google: " << tile.getGoogle()<< "\n"; // Google:  (134494, 194918)
}
```

## Building the Library

*Note*: all commands shown here are expected to be run in the source root of the library.

To configure the build environment, use either:
```
$ cmake -S . -B build
```
if you are using cmake >= 3.13, or:
```
$ mkdir build
$ cd build
$ cmake ..
```
if you are using cmake <= 3.12

Additional configuration options:

- `-DCMAKE_BUILD_TYPE=Release` to enable optimizations. (Default: `Debug`)
- `-DENABLE_GEOTILETEST=OFF` to disable building the tests. (Default `ON`)

Build: `cmake --build build`

Run tests: `cmake --build build --target test`

*Note*: Due to the idiosyncratic separation of 'test execution' from 'building' in CMake, you will have to run the library build before you can run the tests.

## Notes

This repository is a C++ port of (my) [pyGeoTile](https://github.com/geometalab/pyGeoTile).

Further, it is inspired by:

- Tiles à la Google Maps: http://www.maptiler.org/google-maps-coordinates-tile-bounds-projection/
- Bing Maps Tile System: https://msdn.microsoft.com/en-us/library/bb259689.aspx
- Showing pixel and tile coordinates: https://developers.google.com/maps/documentation/javascript/examples/map-coordinates?hl=de
- Mercantile: https://github.com/mapbox/mercantile
