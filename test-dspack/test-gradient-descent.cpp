#include <gtest/gtest.h>
#include "gmock/gmock-matchers.h"
#include "dspack.h"

TEST(test_smoke_gradient_descent, test_smoke_gradient_descent01)
{
    EXPECT_EQ(7 * 6, 42);
}

double naive_square(double x)
{
    return x * x;
}

TEST(test_difference_quotient, test_difference_quotient01)
{
    std::vector<double> result;
    result = difference_quotient(naive_square, {1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 2, 3, 2, 3, 5, 4, 3, 3, 4, 5}, 1);
    result = round_vector(result, 2);
    EXPECT_THAT(result, testing::ElementsAre(3, 3, 3, 3, 3, 3, 5, 5, 5, 6.99, 5, 6.99, 5, 6.99, 10.99, 8.99, 6.99, 6.99, 8.99, 10.99));
}

TEST(test_partial_difference_quotient, test_partial_difference_quotient01)
{
    std::vector<double> result;
    result = partial_difference_quotient(naive_square, {1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 2, 3, 2, 3, 5, 4, 3, 3, 4, 5}, 1, 1);
    result = round_vector(result, 2);
    EXPECT_THAT(result, testing::ElementsAre(3, 3, 3, 3, 3, 3, 5, 5, 5, 6.99, 5, 6.99, 5, 6.99, 10.99, 8.99, 6.99, 6.99, 8.99, 10.99));
}

TEST(test_partial_difference_quotient, test_partial_difference_quotient02)
{
    std::vector<double> result;
    result = partial_difference_quotient(naive_square, {10.0, 2.0}, 0, 1);
    result = round_vector(result, 1);
    EXPECT_THAT(result, testing::ElementsAre(21.0, 5.0));
}

TEST(test_estimate_gradient, test_estimate_gradient01)
{
    std::vector<std::vector<double>> result;
    result = estimate_gradient(naive_square, {1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 2, 3, 2, 3, 5, 4, 3, 3, 4, 5}, 1);
    result = round_matrix(result, 2);
    EXPECT_THAT(result[0], testing::ElementsAre(3, 3, 3, 3, 3, 3, 5, 5, 5, 6.99, 5, 6.99, 5, 6.99, 10.99, 8.99, 6.99, 6.99, 8.99, 10.99));
    EXPECT_THAT(result[1], testing::ElementsAre(3, 3, 3, 3, 3, 3, 5, 5, 5, 6.99, 5, 6.99, 5, 6.99, 10.99, 8.99, 6.99, 6.99, 8.99, 10.99));

}

TEST(test_estimate_gradient, test_estimate_gradient02)
{
    std::vector<std::vector<double>> result;
    result = estimate_gradient(naive_square, {10.0, 2.0}, 1);
    result = round_matrix(result, 1);
    EXPECT_THAT(result[0], testing::ElementsAre(21.0, 5.0));
    EXPECT_THAT(result[1], testing::ElementsAre(21.0, 5.0));
}


// def test_in_random_order():
//     random.seed(0)
//     output = in_random_order(data=[1, 2, 3, 4, 5, 6])
//     assert [_ for _ in output] == [5, 3, 2, 1, 6, 4]

// def test_maximize_batch():
//     x = [[1, 2, 3], [2, 3, 4], [5, 6, 7]]
//     maximize_batch(
//         target_fn=partial(directional_variance, x),
//         gradient_fn=partial(directional_variance_gradient, x),
//         theta_0=[1 for _ in x[0]],
//         tolerance=0.000001
//     )

// def test_maximize_stochastic():
//     x = [
//         [1, 49, 4, 0], [1, 41, 9, 0], [1, 40, 8, 0],
//         [1, 25, 6, 0], [1, 21, 1, 0], [1, 21, 0, 0],
//         [1, 19, 3, 0], [1, 19, 0, 0], [1, 18, 9, 0], [1, 18, 8, 0]
//     ]
//     y = [
//         68.77, 51.25, 52.08,
//         38.36, 44.54, 57.13,
//         51.4, 41.42, 31.22, 34.76,
//     ]
//     maximize_stochastic(
//         target_fn=negate(squared_error),
//         gradient_fn=negate_all(squared_error_gradient),
//         x=x,
//         y=y,
//         theta_0=[random.random() for _ in x[0]],
//         alpha_0=0.01
//     )
