#include "Core.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <limits>

void Core::init(int cpu, Core* other)
{
  m_cpu = cpu;
  m_state = 0;
  m_tsc = 1000000000 + 7777 * cpu;      // Offset of 7777.
  m_other = other;
  r0 = 0;
  r1 = 0;
  r2 = 0;
  s_atomic = 10;
  std::memset(&m_ringbuffer, 0, sizeof(m_ringbuffer));
  std::memset(&m_diff, 0, sizeof(m_diff));
  for (auto&& e : m_diff) e = std::numeric_limits<int64_t>::max();
}

void Core::step()
{
  switch (m_state)
  {
    default:
      m_state = 0;
      //FALL_THROUGH
    case 0:
      r0 = m_tsc;
      break;
    case 1:
      r1 = s_atomic++;
      break;
    case 2:
      r2 = r1 - 1;
      break;
    case 3:
      r1 &= 0x3f;
      break;
    case 4:
      r2 &= 0x3f;
      break;
    case 5:
      m_ringbuffer[r1] = r0;
      break;
    case 6:
      r0 -= m_other->m_ringbuffer[r2];
      break;
    case 7:
      if (r0 < m_diff[r1])
        m_diff[r1] = r0;
      break;
  }
  ++m_state;
}

int Core::s_atomic;
