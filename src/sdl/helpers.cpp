//
// Created by Ignacio Rossi on 4/7/18.
//

#include "helpers.hpp"

bool operator==(const SDL_Rect &r1, const SDL_Rect &r2) {
  return r1.x == r2.x && r1.y == r2.y && r1.w == r2.w && r1.h == r2.h;
}
