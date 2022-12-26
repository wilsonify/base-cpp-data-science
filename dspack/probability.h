#pragma once
#include <cmath>
#include <stdlib.h>
#include <assert.h>
#include <string>

double random_normal();
std::string random_kid();
double uniform_pdf(double x, double a = 0.0, double b = 1.0);
double uniform_cdf(double x, double a = 0, double b = 1);
double normal_pdf(double x, double mu = 0, double sigma = 1);
double normal_cdf(double x, double mu = 0.0, double sigma = 1.0);
double inverse_normal_cdf(double p, double mu = 0, double sigma = 1, double tolerance = 0.00001);
double bernoulli_trial(double p);
int factorial(int m);
int n_choose_k(int n, int k);
double binomial_pmf(int k, int n, double p);
double binomial_cdf(int k, int n, double p);