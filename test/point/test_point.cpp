
#include "point/point.hpp"
#include "prelude.hpp"

using point::IPoint;

SCENARIO("IPoints work as expected", "[point][ipoint]") {
  GIVEN("A new point") {
    IPoint point{2, 3};

    THEN("It has the correct coordinates") {
      REQUIRE(point.x == 2);
      REQUIRE(point.y == 3);
    }
    AND_THEN("I can change the x coordinate") {
      point.x = 5;
      REQUIRE(point.x == 5);
    }
    AND_THEN("I can change the y coordinate") {
      point.y = 7;
      REQUIRE(point.y == 7);
    }
  }

  GIVEN("Two points") {
    const IPoint one{2, 3};
    const IPoint two{5, 7};

    THEN("I can add them") {
      IPoint three = one + two;
      REQUIRE(three.x == 7);
      REQUIRE(three.y == 10);
    }
  }

  GIVEN("Two points") {
    const IPoint one{5, 3};
    const IPoint two{2, 7};

    THEN("I can substract them") {
      IPoint three = one - two;
      REQUIRE(three.x == 3);
      REQUIRE(three.y == -4);
    }
  }

  GIVEN("Two points") {
    IPoint one{2, 3};
    const IPoint two{5, 7};

    THEN("I can add one to the other them") {
      one += two;
      REQUIRE(one.x == 7);
      REQUIRE(one.y == 10);
    }
  }

  GIVEN("Two points") {
    IPoint one{5, 3};
    const IPoint two{2, 7};

    THEN("I can substract one from the other") {
      one -= two;
      REQUIRE(one.x == 3);
      REQUIRE(one.y == -4);
    }
  }

  GIVEN("A point and a scalar") {
    const IPoint point{2, 3};
    int scalar = 5;

    THEN("I can multiply them") {
      IPoint other = point * scalar;
      REQUIRE(other.x == 10);
      REQUIRE(other.y == 15);
    }
  }

  GIVEN("A point and a scalar") {
    IPoint point{2, 3};
    int scalar = 5;

    THEN("I can multiply them in place") {
      point *= scalar;
      REQUIRE(point.x == 10);
      REQUIRE(point.y == 15);
    }
  }

  GIVEN("A point") {
    IPoint point{2, 3};

    THEN("It is equal to itself") {
      testing::assertEquals(point, point);
    }
    AND_THEN("It is equal to another point with the same coordinates") {
      IPoint other{point.x, point.y};
      testing::assertEquals(point, other);
    }
    AND_THEN("It is different to another point which matches the x coordinate only") {
      IPoint other{point.x, 100};
      testing::assertDifferent(point, other);
    }
    AND_THEN("It is different to another point which matches the Y coordinate only") {
      IPoint other{100, point.y};
      testing::assertDifferent(point, other);
    }
    AND_THEN("It is different to another point which matches neither coordinate") {
      IPoint other{100, 100};
      testing::assertDifferent(point, other);
    }
  }
}
