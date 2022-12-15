#include <unordered_map>
#include "linear-algebra.h"

double bucketize(double point, double bucket_size);
std::unordered_map<double, int> make_histogram(std::vector<double> points, double bucket_size);
double mean(std::vector<double> x);
double median(std::vector<double> v);
std::vector<double> mode(std::vector<double> x);

// double correlation_matrix( std::vector<std::vector<double>> data) ;
// double quantile( std::vector<double> x, double p) ;
// double data_range(std::vector<double> x) ;
// double de_mean(std::vector<double> x) ;
// double variance(std::vector<double> x) ;
// double standard_deviation( std::vector<double> x) ;
// double interquartile_range( std::vector<double> x) ;
// double covariance(x, y) ;
// double correlation( std::vector<double> x, std::vector<double> y) ;