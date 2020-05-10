# cppGeoTile

Configure: `cmake -S . -B build`

Additional configuration options:
* `-DCMAKE_BUILD_TYPE=Release` to enable optimizations. (Default: `Debug`)
* `-DENABLE_GEOTILETEST=OFF` to disable building the tests. (Default `ON`)

Build: `cmake --build build`

Run tests: `./build/tests/GeoTileTest`
