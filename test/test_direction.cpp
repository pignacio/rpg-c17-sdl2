/*
 * test_frame_counter.cpp
 * Copyright (C) 2018 irossi <rossi.ignacio@gmail.com>
 *
 * Distributed under terms of the GPLv3 license.
 */

#include <array>
#include <cmath>

#include "direction.hpp"
#include "prelude.hpp"

using point::DPoint;

void assertUnitVector(const Direction &direction, double x, double y) {
  DPoint unit = direction.getUnitVector();
  REQUIRE(fabs(unit.x - x) < 1e-9);
  REQUIRE(fabs(unit.y - y) < 1e-9);
}

const double SQRT2_INVERSE = 1 / std::sqrt(2);

SCENARIO("Directions are assignable and copy-constructibles", "[direction]") {
  GIVEN("Some directions") {
    const Direction one = Direction::UP;
    const Direction two = Direction::DOWN_LEFT;

    THEN("I can assign them and the results are equal to the originals") {
      Direction three = one;
      Direction four = two;
      testing::assertEquals(one, three);
      testing::assertEquals(two, four);
    }
    AND_THEN("I can copy construct them and the results are equal to the originals") {
      Direction three{one};
      Direction four{two};
      testing::assertEquals(one, three);
      testing::assertEquals(two, four);
    }
  }
}

SCENARIO("Directions have the correct unit vectors", "[direction]") {
  GIVEN("The Directions") {
    THEN("They have the correct unit vectors") {
      assertUnitVector(Direction::UP, 0, -1);
      assertUnitVector(Direction::UP_LEFT, -SQRT2_INVERSE, -SQRT2_INVERSE);
      assertUnitVector(Direction::LEFT_UP, -SQRT2_INVERSE, -SQRT2_INVERSE);
      assertUnitVector(Direction::LEFT, -1, 0);
      assertUnitVector(Direction::LEFT_DOWN, -SQRT2_INVERSE, SQRT2_INVERSE);
      assertUnitVector(Direction::DOWN_LEFT, -SQRT2_INVERSE, SQRT2_INVERSE);
      assertUnitVector(Direction::DOWN, 0, 1);
      assertUnitVector(Direction::DOWN_RIGHT, SQRT2_INVERSE, SQRT2_INVERSE);
      assertUnitVector(Direction::RIGHT_DOWN, SQRT2_INVERSE, SQRT2_INVERSE);
      assertUnitVector(Direction::RIGHT, 1, 0);
      assertUnitVector(Direction::RIGHT_UP, SQRT2_INVERSE, -SQRT2_INVERSE);
      assertUnitVector(Direction::UP_RIGHT, SQRT2_INVERSE, -SQRT2_INVERSE);
    }
  }
}

SCENARIO("Diagonal directions match", "[direction]") {
  GIVEN("The diagonal Directions") {
    THEN("They match when appropiate") {
      REQUIRE(Direction::UP_LEFT == Direction::LEFT_UP);
      REQUIRE(Direction::LEFT_DOWN == Direction::DOWN_LEFT);
      REQUIRE(Direction::DOWN_RIGHT == Direction::RIGHT_DOWN);
      REQUIRE(Direction::RIGHT_UP == Direction::UP_RIGHT);
    }
  }
}

#define assertGetDirectionFromUnitVector(x) REQUIRE(x == Direction::getDirection(x.getUnitVector()))

SCENARIO("getDirection resolves directions properly", "[direction]") {
  assertGetDirectionFromUnitVector(Direction::UP);
  assertGetDirectionFromUnitVector(Direction::UP_LEFT);
  assertGetDirectionFromUnitVector(Direction::LEFT_UP);
  assertGetDirectionFromUnitVector(Direction::LEFT);
  assertGetDirectionFromUnitVector(Direction::LEFT_DOWN);
  assertGetDirectionFromUnitVector(Direction::DOWN_LEFT);
  assertGetDirectionFromUnitVector(Direction::DOWN);
  assertGetDirectionFromUnitVector(Direction::DOWN_RIGHT);
  assertGetDirectionFromUnitVector(Direction::RIGHT_DOWN);
  assertGetDirectionFromUnitVector(Direction::RIGHT);
  assertGetDirectionFromUnitVector(Direction::RIGHT_UP);
  assertGetDirectionFromUnitVector(Direction::NONE);
}
