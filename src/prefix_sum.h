#ifndef LAB8_PREFIX_SUM_H
#define LAB8_PREFIX_SUM_H

#include <omp.h>

#include <cmath>
#include <thread>
#include <vector>

template<typename T>
std::vector<T> prefix_sum(const std::vector<T> &vector)
{
  auto result = std::vector<T>(vector.size());
  result[0] = vector[0];
  for (int i = 1; i < result.size(); ++i)
  {
    result[i] = result[i - 1] + vector[i];
  }
  return result;
}

template<typename T>
std::vector<T> prefix_sum_openmp(const std::vector<T> &vector)
{
  const int thread_num = static_cast<const int>(std::thread::hardware_concurrency());
  omp_set_dynamic(0);
  omp_set_num_threads(thread_num);

  std::vector<T> result(vector.size());
  result[0] = vector[0];
  std::vector<T> partial(thread_num);
  partial[0] = T{0};

  const int size = vector.size();
#pragma omp parallel
  {
    const int idx_thread = omp_get_thread_num();

    T sum{0};
    // вычисление префиксных сумм для фрагментов
#pragma omp for schedule(static) nowait
    for (int i = 0; i < size; ++i)
    {
      sum += vector[i];
      result[i] = sum;
    }
    if (idx_thread + 1 < thread_num) // кроме последнего потока
      partial[idx_thread + 1] = sum; // сохранение сумм для каждого потока

#pragma omp barrier

    // вычисление суммы всех предыдущих значений
    T offset{0};
    for (int i = 0; i < idx_thread + 1; ++i)
      offset += partial[i];

#pragma omp for schedule(static)
    for (int i = 0; i < size; ++i)
      result[i] += offset;
  }
  return result;
}

#endif //LAB8_PREFIX_SUM_H
