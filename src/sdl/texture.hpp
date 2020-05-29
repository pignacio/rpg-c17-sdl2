//
// Created by Ignacio Rossi on 4/3/18.
//

#ifndef CLIONTEST_TEXTURE_H
#define CLIONTEST_TEXTURE_H

#include "ptr.hpp"
#include <SDL2/SDL.h>

namespace sdl {

class Texture {
public:
  using ptr = sdl_unique_ptr<SDL_Texture, Texture>;

  virtual ~Texture() = default;

  virtual SDL_Texture *get() const = 0;
  virtual int width() const = 0;
  virtual int height() const = 0;
};

class TextureImpl : public Texture {
public:
  explicit TextureImpl(SDL_Texture *texture, int width, int height);
  TextureImpl(const TextureImpl &s) = default;
  TextureImpl &operator=(const TextureImpl &s) = default;
  virtual ~TextureImpl() = default;

  SDL_Texture *get() const override;
  int width() const override;
  int height() const override;

  static ptr wrap(SDL_Texture *texture, int width, int height);

private:
  SDL_Texture *_texture;
  int _width;
  int _height;

  static void free(SDL_Texture *texture);
};

std::ostream &operator<<(std::ostream &stream, const Texture &texture);

} // namespace sdl

#endif // CLIONTEST_TEXTURE_H
