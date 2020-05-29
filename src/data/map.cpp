#include "data/map.hpp"

#include <utility>

#include "logging.hpp"

namespace data {

Map::Map(int width, int height) : _layer{width, height} {
}

auto Map::set(int x, int y, int value) -> void {
  _layer.set(x, y, value);
}

auto Map::forEach(std::function<void(int, int, int)> consumer) const -> void {
  _layer.forEach(std::move(consumer));
}

} // namespace data
