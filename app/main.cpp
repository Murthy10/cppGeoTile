#include "point.hpp"
#include "tile.hpp"

#include <iostream>

int main()
{
    auto quadTree = "1202211";
    auto tile = Tile::fromQuadTree(quadTree);
    auto tms = tile.getTms();
    std::cout << quadTree << "\n";
    std::cout << std::get<0>(tms) << " " << std::get<1>(tms) << "\n";
    std::cout << tile.getQuadTree() << "\n";
}
