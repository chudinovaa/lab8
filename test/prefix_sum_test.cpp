#include <gtest/gtest.h>

#include <src/prefix_sum.h>

#include <numeric>

inline void vector_eq(const std::vector<int> &actual, const std::vector<int> &expected)
{
  ASSERT_EQ(actual.size(), expected.size());
  for (int i = 0; i < actual.size(); ++i)
  {
    EXPECT_EQ(actual[i], expected[i])
            << "i = " << i <<
            "\nActual: " << actual[i] <<
            "\nExpected: " << expected[i] << std::endl;
  }
}

TEST(prefix_sum_test, test_prefix_sum)
{
  std::vector<int> data(100);
  for (int i = 0; i < data.size(); ++i)
    data[i] = i * i;
  decltype(data) expected(data.size());
  std::partial_sum(std::begin(data), std::end(data), std::begin(expected));
  auto actual = prefix_sum(data);
  vector_eq(actual, expected);

  actual = prefix_sum_openmp(data);
  vector_eq(actual, expected);
}
