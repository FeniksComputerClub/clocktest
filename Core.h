#pragma once

#include <cstdint>
#include <array>
#include <string>

struct Core
{
  static int s_atomic;  // A shared atomic int.

  int m_cpu;            // The CPU number that this Core represents.
  Core* m_other;        // The other core.

  uint64_t m_tsc;       // The Time Stamp Clock of this CPU.
  int m_state;          // The program counter of this CPU.

  // Registers.
  int64_t r0;
  int64_t r1;
  int64_t r2;
  // Two buffers.
  std::array<uint64_t, 64> m_ringbuffer;
  std::array<int64_t, 64> m_diff;

  void init(int cpu, Core* other);
  void step();
  void increment_tsc() { ++m_tsc; }
};
