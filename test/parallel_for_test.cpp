#include <gtest/gtest.h>

#include <src/parallel_for.h>

#include <list>

TEST(ParallelForTest, testFor)
{
  std::vector<int> data{1, 2, 3, 4, 5, 6};
  auto f = [](decltype(data)::iterator it)
  {
    *it *= *it;
  };
  parallel_for(std::begin(data), std::end(data), f);
  for (auto it = std::begin(data); it != std::end(data); ++it)
  {
    int value = std::distance(std::begin(data), it) + 1;
    EXPECT_EQ(*it, (value * value));
  }
}
