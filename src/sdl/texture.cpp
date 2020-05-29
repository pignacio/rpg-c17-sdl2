//
// Created by Ignacio Rossi on 4/3/18.
//

#include "texture.hpp"
#include "../logging.hpp"

namespace sdl {

TextureImpl::TextureImpl(SDL_Texture *texture, int width, int height)
    : _texture{texture}, _width{width}, _height{height} {
  LOG_ASSERT(LOG, _texture != nullptr, "null texture");
  LOG_ASSERT(LOG, _width > 0, "invalid width");
  LOG_ASSERT(LOG, _height > 0, "invalid height");
}

SDL_Texture *TextureImpl::get() const {
  return _texture;
}

int TextureImpl::width() const {
  return _width;
}

int TextureImpl::height() const {
  return _height;
}

Texture::ptr TextureImpl::wrap(SDL_Texture *texture, int width, int height) {
  LOG_INFO(LOG, "Wrapping SDL_Texture[" << texture << "]");
  return make_sdl_ptr<SDL_Texture, Texture>(texture, &TextureImpl::free,
                                            new TextureImpl(texture, width, height));
}

void TextureImpl::free(SDL_Texture *texture) {
  LOG_INFO(LOG, "Destroying SDL_Texture[" << texture << "]")
  SDL_DestroyTexture(texture);
}

std::ostream &operator<<(std::ostream &stream, const Texture &texture) {
  return stream << "Texture[" << texture.get() << "]";
}
} // namespace sdl
