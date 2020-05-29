/*
 * mock_clock.cpp
 * Copyright (C) 2018 irossi <rossi.ignacio@gmail.com>
 *
 * Distributed under terms of the GPLv3 license.
 */

#include "mock_clock.hpp"

#include <chrono>

int64_t MockClock::millis = 0;

MockClock::time_point MockClock::now() {
  MockClock::duration duration{millis};
  return MockClock::time_point{duration};
}

void MockClock::advance(int forward_millis) {
  millis += forward_millis;
}

void MockClock::reset() {
  millis = 0;
}
