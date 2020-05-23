/*
 * enum_array.h
 * Copyright (C) 2020 irossi <rossi.ignacio@gmail.com>
 *
 * Distributed under terms of the GPLv3 license.
 */

#ifndef ENUM_ARRAY_H_
#define ENUM_ARRAY_H_

#include <array>

template <typename ENUM, typename VALUE, unsigned int SIZE> class EnumArray {
public:
  const VALUE &operator[](ENUM key) const {
    return _array[static_cast<unsigned long>(key)];
  }

  VALUE &operator[](ENUM key) {
    return _array[static_cast<unsigned long>(key)];
  }

private:
  std::array<VALUE, SIZE> _array;
};

#endif // ENUM_ARRAY_H_
