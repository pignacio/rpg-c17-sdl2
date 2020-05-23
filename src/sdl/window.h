//
// Created by Ignacio Rossi on 4/1/18.
//

#ifndef CLIONTEST_WINDOW_H
#define CLIONTEST_WINDOW_H

#include "SDL2/SDL.h"
#include "surface.h"

namespace sdl {
class Window {
public:
  using ptr = sdl_unique_ptr<SDL_Window, Window>;
  explicit Window(SDL_Window *window);

  Window(const Window &) = default;

  Window &operator=(const Window &) = default;

  virtual ~Window() = default;

  Surface getScreen() const;

  SDL_Window *get() const;

  static ptr wrap(SDL_Window *window);
  static ptr create(const std::string &window_title, int width, int height, Uint32 window_flags);

private:
  SDL_Window *_window;

  static void free(SDL_Window *window);
};

std::ostream &operator<<(std::ostream &stream, const Window &window);
} // namespace sdl

#endif // CLIONTEST_WINDOW_H
