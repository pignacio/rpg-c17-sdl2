
#include "direction.hpp"

#include <cmath>

using point::DPoint;

const Direction Direction::NONE{0, 0};
const Direction Direction::UP{0, -1};
const Direction Direction::UP_LEFT{-1, -1};
const Direction Direction::LEFT{-1, 0};
const Direction Direction::LEFT_DOWN{-1, 1};
const Direction Direction::DOWN{0, 1};
const Direction Direction::DOWN_RIGHT{1, 1};
const Direction Direction::RIGHT{1, 0};
const Direction Direction::RIGHT_UP{1, -1};

const Direction Direction::LEFT_UP = UP_LEFT;
const Direction Direction::DOWN_LEFT = LEFT_DOWN;
const Direction Direction::RIGHT_DOWN = DOWN_RIGHT;
const Direction Direction::UP_RIGHT = RIGHT_UP;

const Direction Direction::direction_map[3][3] = {
    {Direction::LEFT_UP, Direction::LEFT, Direction::LEFT_DOWN},
    {Direction::UP, Direction::NONE, Direction::DOWN},
    {Direction::RIGHT_UP, Direction::RIGHT, Direction::RIGHT_DOWN},
};

Direction::Direction(double x, double y) {
  double length = std::sqrt(x * x + y * y);
  _unit_vector = {x, y};
  if (length > 0) {
    _unit_vector *= 1.f / length;
  }
}

DPoint Direction::getUnitVector() const {
  return _unit_vector;
}

bool Direction::operator==(const Direction &other) const {
  return _unit_vector == other._unit_vector;
}

bool Direction::operator!=(const Direction &other) const {
  return !(*this == other);
}

std::ostream &operator<<(std::ostream &stream, const Direction &direction) {
  return stream << "Direction[" << direction.getUnitVector() << "]";
}
