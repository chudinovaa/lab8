#include "prefix_sum.h"
#include "parallel_for.h"
#include "measure_time.h"

#include <iostream>

int main()
{
  std::cout << "prefix_sum\n";
  std::vector<int> vector(1000000);
  for (int i = 0; i < vector.size(); ++i)
    vector[i] = i / 2;
  auto seq_time = measure_time(&prefix_sum<int>, vector);
  std::cout << seq_time << std::endl;
  auto omp_time = measure_time(&prefix_sum_openmp<int>, vector);
  std::cout << omp_time << std::endl;

  std::cout << "parallel_for\n";
  auto f = [](decltype(vector)::iterator it)
  { *it -= 1; };
  auto seq_for_time = measure_time([&f](std::vector<int> &v)
                                   {
                                     for (auto &elem: v)
                                     {
                                       elem -= 1;
                                     }
                                   }, vector);
  std::cout << seq_for_time << std::endl;
  auto par_for_time = measure_time(&parallel_for<decltype(vector)::iterator, decltype(f)>,
                                   std::begin(vector), std::end(vector), f);
  std::cout << par_for_time << std::endl;
}
