/*
 * mock_clock.cpp
 * Copyright (C) 2018 irossi <rossi.ignacio@gmail.com>
 *
 * Distributed under terms of the GPLv3 license.
 */

#ifndef CLIONTEST_MOCK_CLOCK_H
#define CLIONTEST_MOCK_CLOCK_H

#include <chrono>

class MockClock {
public:
  using duration = std::chrono::milliseconds;
  using rep = duration::rep;
  using period = duration::period;
  using time_point = std::chrono::time_point<MockClock>;

  static time_point now();
  static void advance(int millis);
  static void reset();

private:
  static int64_t millis;
};

#endif
