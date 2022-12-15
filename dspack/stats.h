#include <unordered_map>
#include "linear-algebra.h"

double bucketize(double point, double bucket_size);
std::unordered_map<double, int> make_histogram(std::vector<double> points, double bucket_size);
double mean(std::vector<double> x);
double median(std::vector<double> v);
std::vector<double> mode(std::vector<double> x);
double quantile(double p, std::vector<double> x);
double data_range(std::vector<double> x);
double interquartile_range(std::vector<double> x);
std::vector<double> de_mean(std::vector<double> x);
double covariance(std::vector<double> x, std::vector<double> y);
double variance(std::vector<double> x);
double standard_deviation(std::vector<double> x);
double correlation(std::vector<double> x, std::vector<double> y);
std::vector<std::vector<double>> correlation_matrix(std::vector<std::vector<double>> data);
