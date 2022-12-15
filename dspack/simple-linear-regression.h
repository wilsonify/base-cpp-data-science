#include "stats.h"

double predict(double alpha, double beta, double x_i);

double error(double alpha, double beta, double x_i, double y_i);

double sum_of_squared_errors(double alpha, double beta, std::vector<double> x, std::vector<double> y);

double beta_from_least_squares_fit(std::vector<double> x, std::vector<double> y);

double alpha_from_beta(std::vector<double> x, std::vector<double> y, double beta);

double total_sum_of_squares(std::vector<double> y);

double r_squared(double alpha, double beta, std::vector<double> x, std::vector<double> y);

double squared_error(double x_i, double y_i, double alpha, double beta);

double squared_error_gradient_alpha(double x_i, double y_i, double alpha, double beta);

double squared_error_gradient_beta(double x_i, double y_i, double alpha, double beta);
