/*
 * test_mock_clock.cpp
 * Copyright (C) 2018 irossi <rossi.ignacio@gmail.com>
 *
 * Distributed under terms of the GPLv3 license.
 */

#include "mock_clock.hpp"
#include "prelude.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;

milliseconds elapsed_time(MockClock::time_point start) {
  return duration_cast<milliseconds>(MockClock::now() - start);
}

SCENARIO("MockClock work as expected", "[mock][clock]]") {
  MockClock::reset();
  auto start = MockClock::now();

  GIVEN("No advances in the clock") {
    THEN("No time has elapsed") {
      REQUIRE(milliseconds{0} == elapsed_time(start));
    }
  }

  GIVEN("An advance of 100 ms") {
    MockClock::advance(100);
    THEN("100 ms have elapsed") {
      REQUIRE(milliseconds{100} == elapsed_time(start));
    }
  }

  GIVEN("A clock reset") {
    MockClock::reset();
    THEN("We are back at the start") {
      REQUIRE(milliseconds{0} == elapsed_time(start));
    }
  }
}
