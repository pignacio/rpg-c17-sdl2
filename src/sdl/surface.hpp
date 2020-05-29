//
// Created by Ignacio Rossi on 4/1/18.
//

#ifndef CLIONTEST_SURFACE_H
#define CLIONTEST_SURFACE_H

#include <memory>

#include "SDL2/SDL.h"
#include "helpers.hpp"
#include "ptr.hpp"

namespace sdl {

class Surface {
public:
  using ptr = sdl_unique_ptr<SDL_Surface, Surface>;
  explicit Surface(SDL_Surface *surface);

  Surface(const Surface &s) = default;

  Surface &operator=(const Surface &s) = default;

  virtual ~Surface() = default;

  SDL_Surface *get() const;

  ptr optimizeFor(const Surface &surface);
  void fillRect(const SDL_Rect &rect, Uint32 color);
  void fill(Uint32 color);
  void blit(const Surface &dest) const;

  static ptr wrap(SDL_Surface *surface);
  static ptr load(const std::string &path);

private:
  SDL_Surface *_surface;

  static void free(SDL_Surface *surface);
};

std::ostream &operator<<(std::ostream &stream, const Surface &surface);

} // namespace sdl

#endif // CLIONTEST_SURFACE_H
