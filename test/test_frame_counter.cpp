/*
 * test_frame_counter.cpp
 * Copyright (C) 2018 irossi <rossi.ignacio@gmail.com>
 *
 * Distributed under terms of the GPLv3 license.
 */

#include "frame_counter.h"
#include "mock_clock.h"
#include "prelude.h"

using std::chrono::milliseconds;

SCENARIO("The FrameCounter counts frames", "[framecounter]") {
  FrameCounter<MockClock> counter;
  GIVEN("A New FrameCounter") {
    THEN("It starts a zero frames") {
      REQUIRE(0 == counter.getFrameCount());
    }
  }
  GIVEN("A couple of new frames") {
    THEN("It updates the frame count accordingly") {
      counter.nextFrameDuration();
      REQUIRE(1 == counter.getFrameCount());
      counter.nextFrameDuration();
      REQUIRE(2 == counter.getFrameCount());
      counter.nextFrameDuration();
      REQUIRE(3 == counter.getFrameCount());
    }
  }
}

SCENARIO("The FrameCounter uses the Clock to calculate the frame duration", "[framecounter]") {
  MockClock::reset();
  FrameCounter<MockClock> counter;
  GIVEN("The clock did not move") {
    THEN("The frames last nothing") {
      REQUIRE(milliseconds{0} == counter.nextFrameDuration());
    }
  }
  GIVEN("The clock advances") {
    MockClock::advance(100);
    THEN("The frame lasts that") {
      REQUIRE(milliseconds{100} == counter.nextFrameDuration());
    }
  }
  GIVEN("The clock advances again") {
    MockClock::advance(150);
    THEN("The frame lasts that again") {
      REQUIRE(milliseconds{150} == counter.nextFrameDuration());
    }
  }
}
