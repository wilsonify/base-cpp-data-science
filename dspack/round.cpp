#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

double round(double value, int decimal_places)
{
    const double multiplier = std::pow(10.0, decimal_places);
    return std::round(value * multiplier) / multiplier;
}

std::vector<double> round_vector(std::vector<double> values, int decimal_places){
    std::vector<double> result;
    result.resize(values.size());
    for(int i : values) {
        result[i] = round(values[i], decimal_places);
    }
    return result;
}