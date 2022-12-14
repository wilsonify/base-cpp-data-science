#include <cmath>
#include <vector>
#include <cassert>
#include <numeric>
#include <functional>

std::vector<double> vector_add(std::vector<double> v, std::vector<double> w)
{
    /* adds two vectors componentwise */
    std::vector<double> result;
    assert(v.size() == w.size());
    result.resize(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        result[i] = v[i] + w[i];
    }
    return result;
}

std::vector<double> vector_subtract(std::vector<double> v, std::vector<double> w)
{
    /* subtracts two vectors componentwise */
    std::vector<double> result;
    assert(v.size() == w.size());
    result.resize(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        result[i] = v[i] - w[i];
    }
    return result;
}

std::vector<double> vector_sum(std::vector<std::vector<double>> vectors)
{
    /* reduce vectors by adding */
    std::vector<double> result;

    result.resize(vectors[0].size());
    for (int i = 0; i < vectors[0].size(); i++)
    {
        result[i] = 0.0;
        for (int j = 0; j < vectors.size(); j++)
        {
            result[i] = result[i] + vectors[j][i];
        }
    }
    return result;
}

std::vector<double> scalar_multiply(double c, std::vector<double> v)
{
    std::vector<double> result;
    result.resize(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        result[i] = c * v[i];
    }
    return result;
}

std::vector<double> vector_mean(std::vector<std::vector<double>> vectors)
{
    /*
    compute the vector whose i-th element is the mean of the
    i-th elements of the input vectors
    */
    double n = vectors.size();
    double c = 1 / n;
    return scalar_multiply(c, vector_sum(vectors));
}

double dot(std::vector<double> v, std::vector<double> w)
{
    /* v_1 * w_1 + ... + v_n * w_n */
    assert(v.size() == w.size());
    double sum_of_elements = 0.0;
    for (int i = 0; i < v.size(); i++)
    {
        sum_of_elements = sum_of_elements + (v[i] * w[i]);
    }
    return sum_of_elements;
}

double sum_of_squares(std::vector<double> v)
{
    /* v_1 * v_1 + ... + v_n * v_n */
    return dot(v, v);
}

double magnitude(std::vector<double> v)
{
    /* The magnitude of a vector is the absolute length of the vector, denoted as ∥a∥. */
    return std::sqrt(sum_of_squares(v));
}

double squared_distance(std::vector<double> v, std::vector<double> w)
{
    return sum_of_squares(vector_subtract(v, w));
}

double distance(std::vector<double> v, std::vector<double> w)
{
    return std::sqrt(squared_distance(v, w));
}

std::pair<double, double> shape(std::vector<std::vector<double>> a_matrix)
{
    double num_rows = a_matrix.size();
    double num_cols = 0;
    if (num_rows > 0)
    {
        num_cols = a_matrix[0].size();
    }
    return {num_rows, num_cols};
}

std::vector<double> get_row(std::vector<std::vector<double>> a_matrix, double i)
{
    return a_matrix[i];
}

std::vector<double> get_column(std::vector<std::vector<double>> a_matrix, double j)
{
    std::vector<double> result;
    result.resize(a_matrix.size());

    for (int i = 0; i < a_matrix.size(); i++)
    {
        result[i] = a_matrix[i][j];
    }

    return result;
}

std::vector<std::vector<double>> make_matrix(double num_rows, double num_cols, std::function<double(int, int)> entry_fn)
{
    // returns a num_rows x num_cols matrix whose (i,j)-th entry is entry_fn(i, j)
    std::vector<std::vector<double>> result;
    result.resize(num_rows);
    for (int i = 0; i < num_rows; i++)
    {
        result[i].resize(num_cols);
        for (int j = 0; j < num_cols; j++)
        {
            result[i][j] = entry_fn(i, j);
        }
    }
    return result;
}

bool is_diagonal(int i, int j)
{
    // 1s on the diagonal, 0s everywhere else
    return i == j;
}

std::vector<std::vector<double>> matrix_add(std::vector<std::vector<double>> a_matrix, std::vector<std::vector<double>> b_matrix)
{
    assert(shape(a_matrix) == shape(b_matrix));
    std::pair<double, double> shape_a_matrix;
    shape_a_matrix = shape(a_matrix);
    double num_rows = shape_a_matrix.first;
    double num_cols = shape_a_matrix.second;
    std::vector<std::vector<double>> result;
    result.resize(num_rows);
    for (int i = 0; i < num_rows; i++)
    {
        result[i].resize(num_cols);
        for (int j = 0; j < num_cols; j++)
        {
            result[i][j] = a_matrix[i][j] + b_matrix[i][j];
        }
    }
    return result;
}