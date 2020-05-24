#ifndef SRC_DATA_MAP_H
#define SRC_DATA_MAP_H

#include <cereal/cereal.hpp>

#include "data/table.h"

namespace data {

class Map {
public:
  Map(int widht, int height);

  auto set(int x, int y, int value) -> void;

  auto forEach(std::function<void(int, int, int)> consumer) const -> void;

  template <typename Archive> void serialize(Archive &ar, [[gnu::unused]] uint32_t version) {
    ar(CEREAL_NVP(_layer));
  }

private:
  Table<int> _layer;
};

} // namespace data

CEREAL_CLASS_VERSION(data::Map, 1);

#endif // SRC_DATA_MAP_H
