#include "GeoTile/point.hpp"
#include "GeoTile/tile.hpp"

#include <iostream>

int main()
{
    auto quadTree = "1202211";
    auto tile = Tile::fromQuadTree(quadTree);
    auto [tmsX, tmsY] = tile.getTms();
    std::cout << quadTree << "\n";
    std::cout << tmsX << " " << tmsY << "\n";
    std::cout << tile.getQuadTree() << "\n";
}
