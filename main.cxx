#include <iostream>
#include <array>
#include <random>
#include "Core.h"

int main()
{
  std::array<Core, 2> cores;

  std::default_random_engine e1(1);
  std::uniform_int_distribution<int> uniform_dist(0, 15);

  for (int i = 0; i < 1000000; ++i)
  {
    int random_number = uniform_dist(e1);
    int core_number = random_number & 1;	// 0 or 1.
    int loop_size = 1 + (random_number >> 1);		// 1 to 8.
    for (int j = 0; j < loop_size; ++j)
    {
      cores[core_number].step();
      Core::increment_tsc();
    }
  }
}
