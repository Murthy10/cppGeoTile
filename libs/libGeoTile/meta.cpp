#include <math.h>

#include "meta.hpp"

double resolution(int zoom)
{
    return INITIAL_RESOLUTION / pow(2, zoom);
}