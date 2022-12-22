#include <vector>
#include <limits>
#include "linear-algebra.h"

std::vector<double> difference_quotient(std::function<double(double)> f, std::vector<double> x, double h)
{
    double eps = 0.001;
    std::vector<double> result;
    result.resize(x.size());
    for (int i = 0; i < x.size(); i++)
    {
        result[i] = (f(x[i] + h) - f(x[i])) / (h + eps);
    }
    return result;
}

std::vector<double> partial_difference_quotient(std::function<double(double)> f, std::vector<double> v, int i, double h)
{
    double eps = 0.001;
    std::vector<double> w;
    std::vector<double> result;

    w.resize(v.size());
    result.resize(v.size());

    for (int j = 0; j < v.size(); j++)
    {
        w[j] = v[j];
        if (j == i)
        {
            // add h to just the i-th element of v
            w[j] = v[j] + h;
        }
    }

    for (int k = 0; k < v.size(); k++)
    {
        result[k] = (f(v[k] + h) - f(v[k])) / (h + eps);
    }
    return result;
}

std::vector<std::vector<double>> estimate_gradient(std::function<double(double)> f, std::vector<double> v, double h = 0.00001)
{
    std::vector<std::vector<double>> result;
    result.resize(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        result[i].resize(v.size());
        result[i] = partial_difference_quotient(f, v, i, h);
    }
    return result;
}

std::vector<double> step(std::vector<double> v, std::vector<double> direction, double step_size)
{
    /*
    move step_size in the direction from v
    */
    assert(v.size() == direction.size());
    std::vector<double> result;
    result.resize(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        result[i] = v[i] + step_size * direction[i];
    }
    return result;
}

std::vector<double> sum_of_squares_gradient(std::vector<double> v)
{
    std::vector<double> result;
    result.resize(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        result[i] = 2 * v[i];
    }
    return result;
}

std::function<double(double)> safe(std::function<double(double)> f)
{
    auto wrapper = [&f](double x)
    {
        double result;
        double largest_double = std::numeric_limits<double>::max();
        try
        {
            result = f(x);
        }
        catch (...)
        {
            result = largest_double;
        }
        return result;
    };
    return wrapper;
}

std::function<double(std::vector<double>)> safe_vector(std::function<double(std::vector<double>)> f)
{
    auto wrapper = [&f](std::vector<double> v)
    {
        double result;
        double largest_double = std::numeric_limits<double>::max();
        try
        {
            result = f(v);
        }
        catch (...)
        {
            result = largest_double;
        }
        return result;
    };
    return wrapper;
}

std::vector<double> minimize_batch(std::function<double(std::vector<double>)> target_fn, std::function<std::vector<double>(std::vector<double>)> gradient_fn, std::vector<double> theta_0, double tolerance = 0.000001)
{
    /*
    use gradient descent to find theta that minimizes target function
    */
    std::vector<double> step_sizes = {100, 10, 1, 0.1, 0.01, 0.001, 0.0001, 0.00001};
    std::vector<double> theta = theta_0; // set theta to initial value
    target_fn = safe_vector(target_fn);  // safe version of target_fn
    double value = target_fn(theta);     // value we're minimizing
    int max_iter = 10000;
    for (int i = 0; i < max_iter; i++)
    {
        std::vector<double> gradient = gradient_fn(theta);
        std::vector<std::vector<double>> next_thetas;
        next_thetas.resize(step_sizes.size());
        for (int j = 0; j < step_sizes.size(); j++)
        {
            next_thetas[j] = step(theta, gradient, -step_sizes[j]);
        }

        // choose the one that minimizes the error function
        double smallest_value = 10000000;
        std::vector<double> next_theta = theta;
        double next_value = target_fn(next_theta);
        for (std::vector<double> possible_theta : next_thetas)
        {
            if (target_fn(possible_theta) < smallest_value)
            {
                next_theta = possible_theta;
                next_value = target_fn(next_theta);
            }
        }
        theta = next_theta;
        value = next_value;
        if (std::abs(value - next_value) < tolerance)
        {
            // stop if we're "converging"
            break;
        }
    }
    return theta;
}

std::vector<std::vector<double>> in_random_order(std::vector<std::vector<double>> data)
{
    /*
    returns the elements of x in random order
     */
    std::vector<std::vector<double>> result;
    result.resize(data.size());
    for (int i = 0; i < data.size(); i++)
    {
        result[i] = data[i];
    }

    for (int i = 0; i < data.size(); i++)
    {
        int random_index = int(std::rand() * data.size());
        int random_index2 = int(std::rand() * data.size());
        std::swap(result[random_index], result[random_index2]);
    }

    return result;
}

std::vector<double> minimize_stochastic(std::function<double(std::vector<double>)> target_fn, std::function<std::vector<double>(std::vector<double>)> gradient_fn, std::vector<double> x, std::vector<double> y, std::vector<double> theta_0, double alpha_0 = 0.01)
{
    std::vector<std::vector<double>> data;
    assert(x.size() == y.size());
    data.resize(x.size());
    for (int i = 0; i < x.size(); i++)
    {
        data[i] = {x[i], y[i]};
    }

    std::vector<double> theta = theta_0; // initial guess
    double alpha = alpha_0;              // initial step size
    std::vector<double> min_theta;
    double min_value = 100000000; // the minimum so far
    int iterations_with_no_improvement = 0;

    // if we ever go 100 iterations with no improvement, stop
    while (iterations_with_no_improvement < 100)
    {
        double value = 0;
        for (std::vector<double> row : data)
        {
            value = value + target_fn(row);
        }
        if (value < min_value)
        {
            // if we've found a new minimum, remember it
            // and go back to the original step size
            min_theta = theta;
            min_value = value;
            iterations_with_no_improvement = 0;
            alpha = alpha_0;
        }
        else
        {
            // otherwise we're not improving, so try shrinking the step size
            iterations_with_no_improvement++;
            alpha = alpha * 0.9;
        }
        // and take a gradient step for each of the data points

        for (std::vector<double> row : in_random_order(data))
        {
            auto gradient_i = gradient_fn(row);
            theta = vector_subtract(theta, scalar_multiply(alpha, gradient_i));
        }
    }
    return min_theta;
}

// double maximize_batch(std::function<double(std::vector<double>)> target_fn, std::function<std::vector<double>(std::vector<double>)> gradient_fn, std::vector<double> theta_0, double tolerance = 0.000001)
// {
//     auto negate_target_fn = [&target_fn](std::vector<double> x)
//     {
//         double result;
//         result = target_fn(x);
//         return -result;
//     };

//     auto negate_gradient_fn = [&gradient_fn](std::vector<double> v)
//     {
//         std::vector<double> result;
//         result.resize(v.size());
//         result = gradient_fn(v);
//         for (int i = 0; i < v.size(); i++)
//         {
//             result[i] = -result[i];
//         }
//         return result;
//     };

//     return minimize_batch(negate_target_fn, negate_gradient_fn, theta_0, tolerance);
// }

// double maximize_stochastic(target_fn, gradient_fn, x, y, theta_0, alpha_0 = 0.01)
//         {
//         return minimize_stochastic(
//             negate(target_fn), negate_all(gradient_fn), x, y, theta_0, alpha_0)
//         }