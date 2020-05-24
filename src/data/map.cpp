#include "data/map.h"

#include "logging.h"

namespace data {

Map::Map(int width, int height) : _layer{width, height} {
}

auto Map::set(int x, int y, int value) -> void {
  _layer.set(x, y, value);
}

auto Map::forEach(std::function<void(int, int, int)> consumer) const -> void {
  LOG_INFO(LOG, "Map::forEach");
  _layer.forEach(consumer);
}

} // namespace data
