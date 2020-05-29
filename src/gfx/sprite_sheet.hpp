//
// Created by Ignacio Rossi on 4/7/18.
//

#ifndef CLIONTEST_SPRITE_SHEET_H
#define CLIONTEST_SPRITE_SHEET_H

#include "../sdl/renderer.hpp"

namespace sdl {
class sdlTexture;
}

namespace gfx {

class SpriteSheet {
public:
  virtual ~SpriteSheet() = default;

  virtual int size() const = 0;
  virtual int width() const = 0;
  virtual int height() const = 0;

  virtual sdl::CopySource get(int index) const = 0;
  virtual sdl::CopySource get(int x, int y) const = 0;
};

class SpriteSheetImpl : public SpriteSheet {
public:
  SpriteSheetImpl(sdl::Texture &texture, int sprite_width, int sprite_height);

  int size() const;
  int width() const;
  int height() const;

  sdl::CopySource get(int index) const;
  sdl::CopySource get(int x, int y) const;

private:
  sdl::Texture &_texture;
  const int _sprite_width;
  const int _sprite_height;
  const int _width;
  const int _height;
};

} // namespace gfx

#endif // CLIONTEST_SPRITE_SHEET_H
