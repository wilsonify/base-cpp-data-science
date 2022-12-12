#include <gtest/gtest.h>
#include "gmock/gmock-matchers.h"
#include "dspack.h"

TEST(mysqrtTests, returns5With25PassedIn)
{
    double result;
    result = mysqrt(25.0);
    EXPECT_EQ(5.0, result);
}

TEST(mysqrtTests, returns0WithNegativePassedIn)
{
    double result;
    result = mysqrt(-25.0);
    EXPECT_EQ(0.0, result);
}

TEST(mysqrtTests, returns10With100PassedIn)
{
    double result;
    result = mysqrt(100.0);
    EXPECT_EQ(10.0, result);
}

TEST(mysqrtTests, returns212With44944PassedIn)
{
    double result;
    result = mysqrt(44944.0);
    result = round(result, 2);
    EXPECT_EQ(212.03, result);
}

TEST(mysqrtvectorTests, mysqrtvector01)
{
    std::vector<double> result;
    result = mysqrt_vector({1, 4, 9, 16, 25});
    EXPECT_THAT(result, testing::ElementsAre(1, 2, 3, 4, 5));
}