#include <gtest/gtest.h>
#include "gmock/gmock-matchers.h"
#include "dspack.h"

TEST(test_smoke_decision_trees, test_smoke_decision_trees01)
{
    EXPECT_EQ(7 * 6, 42);
}

TEST(test_entropy, test_entropy01)
{
    double result;
    result = entropy({0.03465932, 0.66760237, 0.59663384, 0.50902072, 0.70091641, 0.80386941, 0.05129834, 0.82464877, 0.59167620, 0.20355973});
    result = round(result, 2);
    EXPECT_EQ(3.47, result);
}
TEST(test_entropy, test_entropy02)
{
    double result;
    result = entropy({0.3571429, 0.6428571});
    result = round(result, 2);
    EXPECT_EQ(0.94, result);
}
// TEST(mysqrtTests, returns0WithNegativePassedIn)
// {
//     double result;
//     result = mysqrt(-25.0);
//     EXPECT_EQ(0.0, result);
// }

// TEST(mysqrtvectorTests, mysqrtvector01)
// {
//     std::vector<double> result;
//     result = mysqrt_vector({1, 4, 9, 16, 25});
//     EXPECT_THAT(result, testing::ElementsAre(1, 2, 3, 4, 5));
// }