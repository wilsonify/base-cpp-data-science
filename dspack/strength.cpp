#include <algorithm>
#include <vector>
#include <cassert>
#include "round.h"

double strength(double actual, double expected)
{
    double result;
    double eps = 0.001;
    result = actual / (expected + eps);
    return result;
}

std::vector<double> strength_vector(std::vector<double> actual, std::vector<double> expected)
{
    std::vector<double> result;
    assert(expected.size() == actual.size());
    result.resize(expected.size());

    for (int i = 0; i < expected.size(); i++)
    {
        result[i] = strength(actual[i], expected[i]);
        result[i] = round(result[i], 2);
    }
    return result;
}
