#include <vector>
#include <limits>
#include "linear-algebra.h"

std::vector<double> difference_quotient(std::function<double(double)> f, std::vector<double> x, double h);
std::vector<double> partial_difference_quotient(std::function<double(double)> f, std::vector<double> v, int i, double h);
std::vector<std::vector<double>> estimate_gradient(std::function<double(double)> f, std::vector<double> v, double h = 0.00001);
std::vector<double> step(std::vector<double> v, std::vector<double> direction, double step_size);
std::vector<double> sum_of_squares_gradient(std::vector<double> v);
std::function<double(double)> safe(std::function<double(double)> f);
std::function<double(std::vector<double>)> safe_vector(std::function<double(std::vector<double>)> f);
std::vector<double> minimize_batch(std::function<double(std::vector<double>)> target_fn, std::function<std::vector<double>(std::vector<double>)> gradient_fn, std::vector<double> theta_0, double tolerance = 0.000001);
std::vector<std::vector<double>> in_random_order(std::vector<std::vector<double>> data);
std::vector<double> minimize_stochastic(std::function<double(std::vector<double>)> target_fn, std::function<std::vector<double>(std::vector<double>)> gradient_fn, std::vector<double> x, std::vector<double> y, std::vector<double> theta_0, double alpha_0 = 0.01);

// double maximize_batch(std::function<double(std::vector<double>)> target_fn, std::function<std::vector<double>(std::vector<double>)> gradient_fn, std::vector<double> theta_0, double tolerance = 0.000001)

// double maximize_stochastic(target_fn, gradient_fn, x, y, theta_0, alpha_0 = 0.01)
