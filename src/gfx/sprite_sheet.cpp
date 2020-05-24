#include <climits> //
// Created by Ignacio Rossi on 4/7/18.
//

#include "sprite_sheet.h"

namespace gfx {

SpriteSheetImpl::SpriteSheetImpl(sdl::Texture &texture, int sprite_width, int sprite_height)
    : _texture{texture}, _sprite_width{sprite_width}, _sprite_height{sprite_height},
      _width{_texture.width() / _sprite_width}, _height{texture.height() / _sprite_height} {
}

int SpriteSheetImpl::size() const {
  return _width * _height;
}

int SpriteSheetImpl::width() const {
  return _width;
}

int SpriteSheetImpl::height() const {
  return _height;
}

sdl::CopySource SpriteSheetImpl::get(int index) const {
  return get(index % _width, index / _width);
}

sdl::CopySource SpriteSheetImpl::get(int x, int y) const {
  LOG_ASSERT(LOG, 0 <= x && x < _width, "Invalid x-index:" << x << " (width:" << _width << ")");
  LOG_ASSERT(LOG, 0 <= y && y < _height, "Invalid y-index:" << y << " (height:" << _height << ")");
  SDL_Rect rect{x * _sprite_width, y * _sprite_height, _sprite_width, _sprite_height};
  return {_texture, rect};
}
} // namespace gfx