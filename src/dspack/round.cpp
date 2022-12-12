#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

double round(double value, int decimal_places)
{
    const double multiplier = std::pow(10.0, decimal_places);
    return std::round(value * multiplier) / multiplier;
}
