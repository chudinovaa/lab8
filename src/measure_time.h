#ifndef LAB8_MEASURE_TIME_H
#define LAB8_MEASURE_TIME_H

#include <chrono>

template<typename F, typename... Args>
long measure_time(F f, Args...args)
{
  auto time_begin = std::chrono::system_clock::now();
  f(args...);
  auto time_end = std::chrono::system_clock::now();
  return (time_end - time_begin).count();
}

#endif //LAB8_MEASURE_TIME_H
