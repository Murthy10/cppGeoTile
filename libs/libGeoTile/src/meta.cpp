#include "meta.hpp"

#include <cmath>

double resolution(int zoom)
{
    return INITIAL_RESOLUTION / std::pow(2, zoom);
}

