#include <cmath>
#include <vector>
#include <numeric>
#include <utility>
#include <cassert>

std::vector<double> vector_add(std::vector<double> v, std::vector<double> w);
std::vector<double> vector_subtract(std::vector<double> v, std::vector<double> w);
std::vector<double> vector_sum(std::vector<std::vector<double>> vectors);
std::vector<double> scalar_multiply(double c, std::vector<double> v);
std::vector<double> vector_mean(std::vector<std::vector<double>> vectors);
// std::vector<double> dot(std::vector<double> v, std::vector<double> w);
// double sum_of_squares(std::vector<double> v);
// double magnitude(std::vector<double> v);
// double squared_distance(std::vector<double> v, std::vector<double> w);
// double distance(std::vector<double> v, std::vector<double> w);
// std::pair<double, double> shape(std::vector<std::vector<double>> a_matrix);
// std::vector<double> get_row(std::vector<std::vector<double>> a_matrix, double i);
// std::vector<double> get_column(std::vector<std::vector<double>> a_matrix, double j);
// std::vector<std::vector<double>> make_matrix(double num_rows, double num_cols, entry_fn);
// bool is_diagonal(double i, double j);
// std::vector<std::vector<double>> matrix_add(std::vector<std::vector<double>> a_matrix, std::vector<std::vector<double>> b_matrix);