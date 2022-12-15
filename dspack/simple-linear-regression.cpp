#include "stats.h"

double predict(double alpha, double beta, double x_i)
{
    return beta * x_i + alpha;
}

double error(double alpha, double beta, double x_i, double y_i)
{
    return y_i - predict(alpha, beta, x_i);
}

double sum_of_squared_errors(double alpha, double beta, std::vector<double> x, std::vector<double> y)
{
    double result = 0.0;
    assert(x.size() == y.size());
    for (int i = 0; i < x.size(); i++)
    {
        result = result + std::pow(error(alpha, beta, x[i], y[i]), 2);
    }
    return result;
}

double beta_from_least_squares_fit(std::vector<double> x, std::vector<double> y)
{
    /*given training values for x and y,
    find the least-squares values of alpha and beta*/
    double beta = correlation(x, y) * standard_deviation(y) / standard_deviation(x);
    return beta;
}

double alpha_from_beta(std::vector<double> x, std::vector<double> y, double beta)
{
    double alpha = mean(y) - beta * mean(x);
    return alpha;
}

double total_sum_of_squares(std::vector<double> y)
{
    /* the total squared variation of y_i's from their mean */
    double result = 0.0;
    std::vector<double> de_mean_y = de_mean(y);
    for (int i = 0; i < de_mean_y.size(); i++)
    {
        result = result + pow(de_mean_y[i], 2);
    }
    return result;
}

double r_squared(double alpha, double beta, std::vector<double> x, std::vector<double> y)
{
    /*the fraction of variation in y captured by the model, which equals
    1 - the fraction of variation in y not captured by the model*/
    return 1.0 - (sum_of_squared_errors(alpha, beta, x, y) / total_sum_of_squares(y));
}

double squared_error(double x_i, double y_i, double alpha, double beta)
{

    return pow(error(alpha, beta, x_i, y_i), 2);
}

double squared_error_gradient_alpha(double x_i, double y_i, double alpha, double beta)
{
    return -2 * error(alpha, beta, x_i, y_i); // alpha partial derivative
}

double squared_error_gradient_beta(double x_i, double y_i, double alpha, double beta)
{
    return -2 * error(alpha, beta, x_i, y_i) * x_i; // beta partial derivative
}