#include <gtest/gtest.h>
#include "dspack.h"

TEST(test_smoke_machine_learning, test_smoke_machine_learning01)
{
    EXPECT_EQ(7 * 6, 42);
}

TEST(test_accuracy, test_accuracy01)
{
    double result;
    result = accuracy(1.0, 1.0, 1.0, 1.0);
    EXPECT_EQ(0.49875311720698257, result);
}

TEST(test_accuracy, test_accuracy02)
{
    double result;
    result = accuracy(10.0, 10.0, 10.0, 10.0);
    EXPECT_EQ(0.49987503124218946, result);
}

TEST(test_accuracy, test_accuracy03)
{
    double result;
    result = accuracy(10.0, 100.0, 1000.0, 10000.0);
    EXPECT_EQ(0.90098928803844458, result);
}

TEST(test_accuracy, test_accuracy04)
{
    double result;
    result = accuracy(0.0, 0.0, 0.0, 0.0);
    EXPECT_EQ(0.0, result);
}

TEST(test_accuracy, test_accuracy05)
{
    // (100, 120, 200, 303, pytest.approx(0.55, abs=0.01)),
    double result;
    result = accuracy(100, 120, 200, 303);
    result = round(result, 2);
    EXPECT_EQ(0.56, result);
}
TEST(test_accuracy, test_accuracy06)
{
    // (100, 1, 200, 303, pytest.approx(0.66, abs=0.01)),
    double result;
    result = accuracy(100, 1, 200, 303);
    result = round(result, 2);
    EXPECT_EQ(0.67, result);
}
TEST(test_accuracy, test_accuracy07)
{
    // (0, 120, 200, 303, pytest.approx(0.48, abs=0.01))
    double result;
    result = accuracy(0, 120, 200, 303);
    result = round(result, 2);
    EXPECT_EQ(0.49, result);
}

TEST(test_f1, test_f101)
{
    //(100, 120, 200, 303, pytest.approx(0.38, abs=0.01)),
    double result;
    result = f1_score(100, 120, 200, 303);
    result = round(result, 2);
    EXPECT_EQ(0.38, result);
}
TEST(test_f1, test_f102)
{
    //(100, 1, 200, 303, pytest.approx(0.49, abs=0.01)),
    double result;
    result = f1_score(100, 1, 200, 303);
    result = round(result, 2);
    EXPECT_EQ(0.49, result);
}
TEST(test_f1, test_f103)
{
    //(1, 120, 200, 303, pytest.approx(0.01, abs=0.01))
    double result;
    result = f1_score(1, 120, 200, 303);
    result = round(result, 3);
    EXPECT_EQ(0.004, result);
}

TEST(test_precision, test_precision01)
{
    //(100, 120, 200, 303, pytest.approx(0.45, abs=0.01))
    double result;
    result = precision(100, 120, 200, 303);
    result = round(result, 2);
    EXPECT_EQ(0.45, result);
}
TEST(test_precision, test_precision02)
{
    //(100, 1, 200, 303, pytest.approx(0.99, abs=0.01)),
    double result;
    result = precision(100, 1, 200, 303);
    result = round(result, 2);
    EXPECT_EQ(0.99, result);
}
TEST(test_precision, test_precision03)
{
    //(1, 120, 200, 303, pytest.approx(0.01, abs=0.01))
    double result;
    result = precision(1, 120, 200, 303);
    result = round(result, 2);
    EXPECT_EQ(0.01, result);
}
TEST(test_recall, test_recall01)
{
    //(100, 120, 200, 303, pytest.approx(0.33, abs=0.01)),
    double result;
    result = recall(100, 120, 200, 303);
    result = round(result, 2);
    EXPECT_EQ(0.33, result);
}
TEST(test_recall, test_recall02)
{
    //(100, 1, 200, 303, pytest.approx(0.33, abs=0.01))
    double result;
    result = recall(100, 1, 200, 303);
    result = round(result, 2);
    EXPECT_EQ(0.33, result);
}
TEST(test_recall, test_recall03)
{
    //(1, 120, 200, 303, pytest.approx(0.01, abs=0.01))
    double result;
    result = recall(1, 120, 200, 303);
    result = round(result, 3);
    EXPECT_EQ(0.005, result);
}