//
// Created by Ignacio Rossi on 4/1/18.
//

#include "surface.h"
#include "../logging.h"
#include <SDL2/SDL_image.h>
#include <cassert>

namespace sdl {

Surface::Surface(SDL_Surface *surface) : _surface(surface) {
  if (_surface == nullptr) {
    LOG_THROW(LOG, "Null surface");
  }
}

SDL_Surface *Surface::get() const {
  return _surface;
}

Surface::ptr Surface::optimizeFor(Surface surface) {
  LOG_INFO(LOG, "Optimizing " << *this << " for " << surface);
  return Surface::wrap(SDL_ConvertSurface(get(), surface.get()->format, 0));
}

void Surface::fillRect(const SDL_Rect &rect, Uint32 color) {
  SDL_FillRect(_surface, &rect, color);
}

void Surface::fill(Uint32 color) {
  SDL_FillRect(_surface, nullptr, color);
}

void Surface::blit(Surface dest) const {
  SDL_BlitSurface(get(), nullptr, dest.get(), nullptr);
}

sdl_unique_ptr<SDL_Surface, Surface> Surface::wrap(SDL_Surface *surface) {
  LOG_INFO(LOG, "Wrapping SDL_Surface[" << surface << "]");
  return make_sdl_ptr<SDL_Surface, Surface>(surface, &Surface::free);
}

Surface::ptr Surface::load(const std::string &path) {
  LOG_INFO(LOG, "Loading image '" << path << "'");
  SDL_Surface *surface = IMG_Load(path.c_str());
  LOG_ASSERT(LOG, surface != nullptr, "Could not load image: " << path);
  return Surface::wrap(surface);
}

void Surface::free(SDL_Surface *surface) {
  LOG_INFO(LOG, "Freeing SDL_Surface[" << surface << "]");
  SDL_FreeSurface(surface);
}

std::ostream &operator<<(std::ostream &stream, const Surface &surface) {
  return stream << "Surface[" << surface.get() << "]";
}
} // namespace sdl