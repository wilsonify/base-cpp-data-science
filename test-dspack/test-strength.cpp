#include <gtest/gtest.h>
#include "gmock/gmock-matchers.h"
#include "dspack.h"

TEST(test_strength, test_strength01)
{
    double result;
    result = strength(25.0, 50.0);
    result = round(result, 1);
    EXPECT_EQ(0.5, result);
}

TEST(test_strength, test_strength02)
{
    double result;
    result = strength(-25.0, 20.0);
    result = round(result, 1);
    EXPECT_EQ(-1.2, result);
}

TEST(test_strength, test_strength03)
{
    double result;
    result = strength(100.0, 100.0);
    result = round(result, 1);
    EXPECT_EQ(1.0, result);
}

TEST(test_strength, test_strength04)
{
    double result;
    result = strength(44944.0, 50000.0);
    result = round(result, 2);
    EXPECT_EQ(0.9, result);
}

TEST(test_strength_vector, test_strength_vector01)
{
    std::vector<double> result;
    result = strength_vector({1, 4, 9, 16, 25}, {25, 25, 25, 25, 25});
    EXPECT_THAT(result, testing::ElementsAre(0.04, 0.16, 0.36, 0.64, 1.0));
}