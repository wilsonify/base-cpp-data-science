#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <array>
#include "linear-algebra.h"

double bucketize(double point, double bucket_size)
{
    /* floor the point to the next lower multiple of bucket_size */
    return bucket_size * std::floor(point / bucket_size);
}

std::unordered_map<double, int> make_histogram(std::vector<double> points, double bucket_size)
{
    /* buckets the points and counts how many in each bucket */
    std::unordered_map<double, int> counter;
    for (int i = 0; i < points.size(); i++)
    {
        double point = points[i];
        int bucket = bucketize(point, bucket_size);
        counter[bucket]++;
    }
    return counter;
}

double mean(std::vector<double> x)
{
    double result = 0.0;
    double eps = 0.001;
    double n = x.size();
    for (int i = 0; i < n; i++)
    {
        result = result + x[i];
    }
    result = result / (n + eps);
    return result;
}

std::vector<double> de_mean(std::vector<double> x)
{
    /* translate x by subtracting its mean (so the result has mean 0) */
    double x_bar = mean(x);
    std::vector<double> result;
    result.resize(x.size());
    for (int i = 0; i < x.size(); i++)
    {
        result[i] = x[i] - x_bar;
    }
    return result;
}

double variance(std::vector<double> x)
{
    /* assumes x has at least two elements */
    int n = x.size();
    std::vector<double> deviations = de_mean(x);
    return sum_of_squares(deviations) / (n - 1);
}

double standard_deviation(std::vector<double> x)
{
    return std::sqrt(variance(x));
}

double covariance(std::vector<double> x, std::vector<double> y)
{
    int n = x.size();
    return dot(de_mean(x), de_mean(y)) / (n - 1);
}

double correlation(std::vector<double> x, std::vector<double> y)
{
    double stdev_x = standard_deviation(x);
    double stdev_y = standard_deviation(y);
    double result = 0.0;
    if (stdev_x > 0 && stdev_y > 0)
    {
        return covariance(x, y) / (stdev_x * stdev_y);
    }
    return result;
}

std::vector<std::vector<double>> correlation_matrix(std::vector<std::vector<double>> data)
{
    /*returns the num_columns x num_columns matrix whose (i, j)th entry
    is the correlation between columns i and j of data*/

    std::pair<int, int> shape_data = shape(data);
    int num_rows = shape_data.first;
    int num_cols = shape_data.second;
    int result_num_rows = shape_data.second;
    int result_num_cols = shape_data.second;
    std::vector<std::vector<double>> result;
    result.resize(result_num_rows);
    for (int i = 0; i < result_num_rows; i++)
    {
        result[i].resize(result_num_cols);
        for (int j = 0; j < result_num_cols; j++)
        {
            result[i][j] = correlation(get_column(data, i), get_column(data, j));
        }
    }

    return result;
}

double median(std::vector<double> v)
{
    /* finds the 'middle-most' value of v */
    std::vector<double> workingcopy = v;
    double result;
    int n = v.size() - 1;
    int midpoint_low = std::floor(n / 2.0);
    int midpoint_high = std::ceil(n / 2.0);
    std::nth_element(workingcopy.begin(), workingcopy.begin() + midpoint_low, workingcopy.end());
    result = (workingcopy[midpoint_low] + workingcopy[midpoint_high]) / 2.0;
    return result;
}

std::vector<double> mode(std::vector<double> x)
{
    /* returns a vector since there might be more than one mode */
    std::unordered_map<double, int> counts;
    std::vector<double> result = {};
    double max_count = 0;

    for (int i = 0; i < x.size(); i++)
    {
        counts[x[i]]++;
        if (counts[x[i]] > max_count)
        {
            max_count = counts[x[i]];
        }
    }

    for (auto &it : counts)
    {
        double key = it.first;
        int value = it.second;
        if (value == max_count)
        {
            result.push_back(key);
        }
    }

    return result;
}

double quantile(double p, std::vector<double> x)
{
    /* returns the pth-percentile value in x */
    std::vector<double> workingcopy = x;
    double result;
    int n = x.size() - 1;
    int p_index = std::floor(p * x.size());
    std::nth_element(workingcopy.begin(), workingcopy.begin() + p_index, workingcopy.end());
    result = workingcopy[p_index];
    return result;
}

double interquartile_range(std::vector<double> x)
{
    return quantile(0.75, x) - quantile(0.25, x);
}

// "range" already means something in Python, so we'll use a different name
double data_range(std::vector<double> x)
{
    double maximum = 0;
    double minimum = 100000000;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] > maximum)
        {
            maximum = x[i];
        }
        if (x[i] < minimum)
        {
            minimum = x[i];
        }
    }
    double result = maximum - minimum;
    return result;
}
