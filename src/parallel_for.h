#ifndef LAB8_PARALLEL_FOR_H
#define LAB8_PARALLEL_FOR_H

#include <cmath>
#include <iterator>
#include <mutex>
#include <thread>
#include <vector>

template<typename It, typename F>
void parallel_for(It begin, It end, F f)
{
  auto distance = std::distance(begin, end);
  auto thread_count = std::thread::hardware_concurrency();
  std::vector<std::thread> thread;
  thread.reserve(thread_count);
  int start_pos = 0;
  while (distance || thread_count)
  {
    int size = std::ceil(distance / static_cast<double>(thread_count));
    int end_pos = start_pos + size;
    It it_start = begin;
    It it_end = begin;
    std::advance(it_start, start_pos);
    std::advance(it_end, end_pos);
    thread.emplace_back(std::thread{
      [](It begin, It end, F f)
      {
        for (auto it = begin; it != end; ++it)
        {
          f(it);
        }
      }, it_start, it_end, f
    });

    start_pos = end_pos;
    distance -= size;
    --thread_count;
  }

  for (auto &t : thread)
    t.join();
}

#endif //LAB8_PARALLEL_FOR_H
