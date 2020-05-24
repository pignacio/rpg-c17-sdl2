#ifndef SRC_DATA_TABLE_H
#define SRC_DATA_TABLE_H

#include <vector>

#include "utils/assert.h"

namespace data {

template <typename T>
class Table {
public:
  Table(int width, int height) : _width{width}, _height{height}, _data{} {
  }

  auto get(int x, int y) const -> T {
    auto index = _index(x, y);
    if (index >= _data.size())
      return {};
    return _data[index];
  }

  auto set(int x, int y, int value) -> void {
    auto index = _index(x, y);
    if (_data.size() < index + 1) {
      _data.resize(index + 1);
    }
    _data[index] = value;
  }

  auto width() const -> int {
    return _width;
  }

  auto height() const -> int {
    return _height;
  }

  auto forEach(std::function<void(int, int, const T&)> consumer) const -> void {
    for (int y = 0; y < _height; ++y) {
      for (int x = 0; x < _width; ++x) {
        consumer(x, y, get(x, y));
      }
    }
  }

private:
  int _width;
  int _height;
  std::vector<T> _data;

  inline unsigned long _index(int x, int y) const {
    utils::checkIndex(x, _width, "x");
    utils::checkIndex(y, _height, "x");
    return static_cast<unsigned long>(y * _width + x);
  }
};

}  // namespace data

#endif  // SRC_DATA_TABLE_H
