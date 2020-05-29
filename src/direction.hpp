#ifndef CLIONTEST_DIRECTION_H
#define CLIONTEST_DIRECTION_H

#include "point/point.hpp"

#include "logging.hpp"
#include <array>
#include <cmath>

class Direction {
public:
  Direction(const Direction &direction) = default;
  Direction &operator=(const Direction &direction) = default;

  point::DPoint getUnitVector() const;

  const static Direction NONE;
  const static Direction UP;
  const static Direction UP_LEFT;
  const static Direction LEFT_UP;
  const static Direction LEFT;
  const static Direction LEFT_DOWN;
  const static Direction DOWN_LEFT;
  const static Direction DOWN;
  const static Direction DOWN_RIGHT;
  const static Direction RIGHT_DOWN;
  const static Direction RIGHT;
  const static Direction RIGHT_UP;
  const static Direction UP_RIGHT;

  template <typename T> static Direction getDirection(point::Point<T> direction);

  bool operator==(const Direction &other) const;
  bool operator!=(const Direction &other) const;

private:
  Direction(double x, double y);
  point::DPoint _unit_vector;

  static const Direction direction_map[3][3];
};

template <typename T> int sign(T value) {
  return fabs(value) < 1e-8 ? 0 : (value > 0 ? 1 : -1);
}

template <typename T> Direction Direction::getDirection(point::Point<T> direction) {
  return direction_map[sign(direction.x) + 1][sign(direction.y) + 1];
}

std::ostream &operator<<(std::ostream &stream, const Direction &direction);

template<typename T>
class DirectionMap {
public:
  const T& operator[](Direction d) const {
    return _array[index(d)];
  }

  T& operator[](Direction d){
    return _array[index(d)];
  }

private:
  std::array<T, 9> _array;

  unsigned long index(Direction d) {
    auto vector = d.getUnitVector();
    return  static_cast<unsigned long>(sign(vector.x) + 1 + 3 * (sign(vector.y) + 1));
  }
};

#endif
