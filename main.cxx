#include <iostream>
#include <array>
#include <random>
#include <limits>
#include "Core.h"

int main()
{
  std::array<Core, 2> cores;

  std::default_random_engine e1(1);
  std::uniform_int_distribution<int> uniform_dist(1, 100);

  cores[0].init(0, &cores[1]);
  cores[1].init(1, &cores[0]);

  for (int i = 0; i < 1000000; ++i)
  {
    int core_number = i & 1;	                        // 0 or 1.
    int loop_size = uniform_dist(e1);                   // 1 to 6.
    for (int j = 0; j < loop_size; ++j)
    {
      cores[core_number].step();
      cores[0].increment_tsc();
      cores[1].increment_tsc();
    }
  }

  int64_t min[2] = { std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::max() };
  for (int cpu = 0; cpu <= 1; ++cpu)
    for (auto&& e : cores[cpu].m_diff)
      min[cpu] = std::min(min[cpu], e);
  int64_t offset = (min[0] - min[1]) / 2;
  int ahead = 0;
  if (offset < 0)
  {
    offset = -offset;
    ahead = 1;
  }
  std::cout << "The Time Stamp Counter of CPU " << ahead << " is " << offset << " ahead of the Time Stamp Counter of CPU " << (1 - ahead) << "." << std::endl;
}
