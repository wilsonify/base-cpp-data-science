#include <gtest/gtest.h>
#include "gmock/gmock-matchers.h"
#include "dspack.h"

TEST(smokeTestLA, BasicAssertionLA)
{
    EXPECT_EQ(7 * 6, 42);
}
TEST(test_vector_add, test_vector_add01)
{
    //([1], [1], [2]),
    std::vector<double> result = vector_add({1}, {1});
    EXPECT_THAT(result, testing::ElementsAre(2));
}

TEST(test_vector_add, test_vector_add02)
{
    //([1, 0, 0, 1], [1, 2, 3, 4], [2, 2, 3, 5])
    std::vector<double> result = vector_add({1, 0, 0, 1}, {1, 2, 3, 4});
    EXPECT_THAT(result, testing::ElementsAre(2, 2, 3, 5));
}

TEST(test_vector_subtract, test_vector_subtract01)
{
    //([1], [1], [0])
    std::vector<double> result = vector_subtract({1}, {1});
    EXPECT_THAT(result, testing::ElementsAre(0));
}

TEST(test_vector_subtract, test_vector_subtract02)
{
    //([1, 0, 0, 1], [1, 2, 3, 4], [0, -2, -3, -3])
    std::vector<double> result = vector_subtract({1, 0, 0, 1}, {1, 2, 3, 4});
    EXPECT_THAT(result, testing::ElementsAre(0, -2, -3, -3));
}

TEST(test_vector_subtract, test_vector_subtract03)
{
    std::vector<double> result = vector_subtract({1, 1, 1}, {10, 10, 10});
    EXPECT_THAT(result, testing::ElementsAre(-9, -9, -9));
}

TEST(test_vector_sum, test_vector_sum01)
{
    //([1], [1], [2])
    std::vector<double> result = vector_sum({{1}, {1}});
    EXPECT_EQ(result.size(), 1);
    EXPECT_THAT(result, testing::ElementsAre(2));
}

TEST(test_vector_sum, test_vector_sum02)
{
    //([1, 0, 0, 1], [1, 2, 3, 4], [2, 2, 3, 5])
    std::vector<double> result = vector_sum({{1, 0, 0, 1}, {1, 2, 3, 4}});
    EXPECT_EQ(result.size(), 4);
    EXPECT_THAT(result, testing::ElementsAre(2, 2, 3, 5));
}
TEST(test_scalar_multiply, test_scalar_multiply01)
{
    // ([2, 1], 1.87, [3.74, 1.87])
    std::vector<double> result = scalar_multiply(1.87, {2, 1});
    EXPECT_EQ(result.size(), 2);
    EXPECT_THAT(result, testing::ElementsAre(3.74, 1.87));
}
TEST(test_scalar_multiply, test_scalar_multiply02)
{
    // ([1, 2, 3, 4], 5, [5, 10, 15, 20])
    std::vector<double> result = scalar_multiply(5.0, {1, 2, 3, 4});
    EXPECT_EQ(result.size(), 4);
    EXPECT_THAT(result, testing::ElementsAre(5, 10, 15, 20));
}

TEST(test_vector_mean, test_vector_mean01)
{
    // ([1], [1], [1])
    std::vector<double> result = vector_mean({{1}, {1}});
    EXPECT_EQ(result.size(), 1);
    EXPECT_THAT(result, testing::ElementsAre(1.0));
}

TEST(test_vector_mean, test_vector_mean02)
{
    // ([1, 0, 0, 1], [1, 2, 3, 4], [1, 1, 1.5, 2.5])
    std::vector<double> result = vector_mean({{1, 0, 0, 1}, {1, 2, 3, 4}});
    EXPECT_EQ(result.size(), 4);
    EXPECT_THAT(result, testing::ElementsAre(1, 1, 1.5, 2.5));
}

TEST(test_dot, test_dot01)
{
    // ([1, 1, 1], [10, 10, 10], 30),
    double result = dot({1, 1, 1}, {10, 10, 10});
    EXPECT_EQ(result, 30);
}
TEST(test_dot, test_dot02)
{
    // ([1, 1, 1], [-10, -10, -10], -30))
    double result = dot({1, 1, 1}, {-10, -10, -10});
    EXPECT_EQ(result, -30);
}

TEST(test_sum_of_squares, test_sum_of_squares01)
{
    // ([1], 1),
    double result = sum_of_squares({1});
    EXPECT_EQ(result, 1);
}

TEST(test_sum_of_squares, test_sum_of_squares02)
{
    // ([1, 0, 0, 1], 2),
    double result = sum_of_squares({1, 0, 0, 1});
    EXPECT_EQ(result, 2);
}

TEST(test_sum_of_squares, test_sum_of_squares03)
{
    // ([1, 2, 3, 4], 30)
    double result = sum_of_squares({1, 2, 3, 4});
    EXPECT_EQ(result, 30);
}

TEST(test_sum_of_squares, test_sum_of_squares04)
{

    double result = sum_of_squares({-9, -9, -9});
    EXPECT_EQ(result, 243);
}

TEST(test_magnitude, test_magnitude01)
{
    // ([10, 10, 10], math.sqrt(30)),
    double result = magnitude({10, 10, 10});
    result = round(result, 2);
    EXPECT_EQ(result, 17.32);
}

TEST(test_magnitude, test_magnitude02)
{
    // ([-10, -10, -10], math.sqrt(30)))
    double result = magnitude({-10, -10, -10});
    result = round(result, 2);
    EXPECT_EQ(result, 17.32);
}

TEST(test_squared_distance, test_squared_distance01)
{
    // ([1], [1], 0),
    double result = squared_distance({1}, {1});
    EXPECT_EQ(result, 0.0);
}
TEST(test_squared_distance, test_squared_distance02)
{
    // ([1, 0, 0, 1], [1, 2, 3, 4], 22)
    double result = squared_distance({1, 0, 0, 1}, {1, 2, 3, 4});
    result = round(result, 2);
    EXPECT_EQ(result, 22.0);
}

TEST(test_squared_distance, test_squared_distance03)
{
    double result = squared_distance({1, 1, 1}, {10, 10, 10});
    result = round(result, 2);
    EXPECT_EQ(result, 243);
}

TEST(test_distance, test_distance01)
{
    // ([0, 0, 0], [10, 10, 10], math.sqrt(30)),
    double result = distance({1, 1, 1}, {10, 10, 10});
    result = round(result, 2);
    EXPECT_EQ(result, 15.59);
}

TEST(test_distance, test_distance02)
{
    // ([0, 0, 0], [-10, -10, -10], math.sqrt(30)))
    double result = distance({1, 1, 1}, {-10, -10, -10});
    result = round(result, 2);
    EXPECT_EQ(result, 19.05);
}

TEST(test_shape, test_shape01)
{
    std::pair<double, double> result = shape({{1, 1, 1}, {-10, -10, -10}});
    EXPECT_EQ(result.first, 2);
    EXPECT_EQ(result.second, 3);
}

TEST(test_get_row, test_get_row01)
{
    std::vector<double> result = get_row({{1, 1, 1}, {-10, -10, -10}}, 0);
    EXPECT_THAT(result, testing::ElementsAre(1, 1, 1));
}

TEST(test_get_row, test_get_row02)
{

    // ([[1], [2], [3]], 0, [1]),
    std::vector<double> result = get_row({{1}, {2}, {3}}, 0);
    EXPECT_THAT(result, testing::ElementsAre(1));
}
TEST(test_get_row, test_get_row03)
{
    // ([[1], [2], [3]], 2, [3]))
    std::vector<double> result = get_row({{1}, {2}, {3}}, 2);
    EXPECT_THAT(result, testing::ElementsAre(3));
}

TEST(test_get_column, test_get_column01)
{
    std::vector<double> result = get_column({{1, 1, 1}, {-10, -10, -10}}, 0);
    EXPECT_THAT(result, testing::ElementsAre(1, -10));
}

TEST(test_get_column, test_get_column02)
{
    // ([[1, 2, 3]], 0, [1]),
    std::vector<double> result = get_column({{1, 2, 3}}, 0);
    EXPECT_THAT(result, testing::ElementsAre(1));
}
TEST(test_get_column, test_get_column03)
{
    // ([[1, 2, 3]], 2, [3]))
    std::vector<double> result = get_column({{1, 2, 3}}, 2);
    EXPECT_THAT(result, testing::ElementsAre(3));
}

TEST(test_make_matrix, test_make_matrix01)
{
    // 5x5 identity matrix
    std::vector<std::vector<double>> result = make_matrix(5, 5, is_diagonal);
    EXPECT_THAT(result[0], testing::ElementsAre(1, 0, 0, 0, 0));
    EXPECT_THAT(result[1], testing::ElementsAre(0, 1, 0, 0, 0));
    EXPECT_THAT(result[2], testing::ElementsAre(0, 0, 1, 0, 0));
    EXPECT_THAT(result[3], testing::ElementsAre(0, 0, 0, 1, 0));
    EXPECT_THAT(result[4], testing::ElementsAre(0, 0, 0, 0, 1));
}

TEST(test_matrix_add, test_matrix_add01)
{
    //([[1]], [[1]], [[2]])
    std::vector<std::vector<double>> result = matrix_add({{1}}, {{1}});
    EXPECT_THAT(result[0], testing::ElementsAre(2));
}
TEST(test_matrix_add, test_matrix_add02)
{

    // ([[1, 0], [0, 1]], [[1, 2], [3, 4]], [[2, 2], [3, 5]])
    std::vector<std::vector<double>> result = matrix_add({{1, 0}, {0, 1}}, {{1, 2}, {3, 4}});
    EXPECT_THAT(result[0], testing::ElementsAre(2,2));
    EXPECT_THAT(result[1], testing::ElementsAre(3,5));
}
