#ifndef CLIONTEST_POINT_H
#define CLIONTEST_POINT_H

#include <iostream>

namespace point {

template <typename T> struct Point {
public:
  Point() = default;
  Point(T xx, T yy) : x{xx}, y{yy} {
  }

  Point operator+(const Point<T> other) const {
    return {x + other.x, y + other.y};
  }

  Point operator-(const Point<T> other) const {
    return {x - other.x, y - other.y};
  }

  template <typename U> Point operator*(U scalar) const {
    return {x * scalar, y * scalar};
  }

  void operator+=(const Point<T> other) {
    x += other.x;
    y += other.y;
  }

  void operator-=(const Point<T> other) {
    x -= other.x;
    y -= other.y;
  }

  template <typename U> void operator*=(U scalar) {
    x *= scalar;
    y *= scalar;
  }

  bool operator==(const Point<T> other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Point<T> other) const {
    return !(*this == other);
  }

  T x;
  T y;
};

template <typename T> std::ostream &operator<<(std::ostream &stream, const Point<T> point) {
  return stream << "Point(" << point.x << ", " << point.y << ")";
}

using IPoint = Point<int>;
using DPoint = Point<double>;

} // namespace point

#endif