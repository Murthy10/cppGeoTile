#include <math.h>

#include <meta.h>

double resolution(int zoom)
{
    return INITIAL_RESOLUTION / pow(2, zoom);
}