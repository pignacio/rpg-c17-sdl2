#ifndef SRC_DATA_MAP_H
#define SRC_DATA_MAP_H

#include "data/table.h"

namespace data {

class Map {
public:
  Map(int widht, int height);
private:
  Table<int> _layer;
};

} // namespace data

#endif  // SRC_DATA_MAP_H
