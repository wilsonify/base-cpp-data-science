#include <cmath>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <vector>
#include <iostream>
#include <string_view>

std::string random_kid()
{
     std::vector<std::string> arrayNum = {"boy", "girl"};
     int RandIndex = rand() % 2; // generates a random integer between 0 and 1
     return arrayNum[RandIndex];
}

double uniform_pdf(double x, double a = 0, double b = 1)
{
     assert(b > a);
     if (a <= x & x < b)
     {
          return 1 / (b - a);
     }
     else
     {
          return 0;
     }
}

double uniform_cdf(double x, double a = 0, double b = 1)
{
     /* returns the probability that a uniform random variable is less than x */
     if (x < a)
     {
          return 0;
     }
     if (a < x & x < b)
     {
          return (x - a) / (b - a); // e.g. P(X < 0.4) = 0.4
     }
     if (b <= x)
     {
          return 1;
     }
     return 0;
}

double normal_pdf(double x, double mu = 0.0, double sigma = 1.0)
{
     double num;
     double denom;
     num = std::exp(-std::pow((x - mu), 2) / 2.0 / std::pow(sigma, 2));
     denom = std::sqrt(2 * M_PI) * sigma;
     return num / denom;
}

double normal_cdf(double x, double mu = 0.0, double sigma = 1.0)
{
     return (1.0 + std::erf((x - mu) / std::sqrt(2.0) / sigma)) / 2.0;
}

double inverse_normal_cdf(double p, double mu = 0, double sigma = 1, double tolerance = 0.00001)
{
     /* find approximate inverse using binary search */
     // if not standard, compute standard and rescale
     bool is_centered = mu == 0;
     bool is_scaled = sigma == 1;
     bool is_standard = is_centered & is_scaled;
     double low_z = -10.0;
     double low_p = 0.0;
     double hi_z = 10.0;
     double hi_p = 1.0;
     double mid_z = (low_z + hi_z) / 2.0;
     double mid_p = normal_cdf(mid_z);

     while (std::abs(mid_p - p) > tolerance)
     {
          mid_z = (low_z + hi_z) / 2.0; // consider the midpoint
          mid_p = normal_cdf(mid_z);    // and the cdf's value there
          if (mid_p < p)
          {
               // midpoint is too low, search above it
               low_z = mid_z;
               low_p = mid_p;
          }
          if (mid_p > p)
          {
               // midpoint is too high, search below it
               hi_z = mid_z;
               hi_p = mid_p;
          }
     }
     if (!is_standard)
     {
          mid_z = mu + sigma * mid_z;
     }
     return mid_z;
}

double random_normal()
{
     /* returns a random draw from a standard normal distribution */
     double x = std::rand();
     std::cout << "x=";
     std::cout << x;
     return inverse_normal_cdf(x);
}

double bernoulli_trial(double p)
{
     /*
     a binomial trial is a random experiment with exactly two possible outcomes.
     the probability of success is the same every time the experiment is conducted.
     */
     if (rand() < p)
     {
          return 1;
     }
     else
     {
          return 0;
     }
}

int factorial(int m)
{
     int result = m;
     for (int i = 0; i < m; i++)
     {
          result *= (result - 1);
     }
     return result;
}

int n_choose_k(int n, int k)
{
     return factorial(n) / (factorial((n - k)) * (factorial(k)));
}

double binomial_pmf(int n, int k, double p)
{
     return n_choose_k(n, k) * std::pow(p, k) * std::pow((1 - p), (n - k));
}

double binomial_cdf(int n, int k, double p)
{
     double result = 0.0;
     for (int i = 0; i < n; i++)
     {
          result = result + binomial_pmf(i, k, p);
     }
     return result;
}
