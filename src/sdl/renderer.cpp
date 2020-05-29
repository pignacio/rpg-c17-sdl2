//
// Created by Ignacio Rossi on 4/1/18.
//

#include "renderer.hpp"

#include "../logging.hpp"
#include "surface.hpp"
#include <memory>

namespace sdl {

Renderer::Renderer(SDL_Renderer *renderer, const Window &window)
    : _renderer(renderer), _window{window} {
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(_renderer);
}

std::unique_ptr<Renderer> Renderer::init(const Window &window, Uint32 renderer_flags) {

  LOG_INFO(LOG, "Creating SDL renderer for " << window << ". Flags: " << renderer_flags);
  auto renderer = SDL_CreateRenderer(window.get(), -1, renderer_flags);

  LOG_ASSERT(LOG, renderer != nullptr, "Could not create renderer!");
  return std::make_unique<Renderer>(renderer, window);
}

Window Renderer::getWindow() const {
  return _window;
}

Texture::ptr Renderer::createTexture(const Surface &surface) const {
  LOG_INFO(LOG, "Creating a texture from" << surface);
  SDL_Surface *sdlSurface = surface.get();
  return TextureImpl::wrap(SDL_CreateTextureFromSurface(_renderer, sdlSurface), sdlSurface->w,
                           sdlSurface->h);
}

void Renderer::clear() {
  // TODO(irossi): ignoring return value
  SDL_RenderClear(_renderer);
}

void Renderer::copy(const CopySource &source, const CopyDest &dest) {
  // Todo ignoring return value
  auto rect = dest.asRect(source.width(), source.height());
  SDL_RenderCopy(_renderer, source.texture().get(), source.rect(), &rect);
}

void Renderer::present() {
  SDL_RenderPresent(_renderer);
}

CopySource::CopySource(Texture &texture) : _texture{texture}, _rect{} {
}

CopySource::CopySource(Texture &texture, SDL_Rect rect) : _texture{texture}, _rect{rect} {
}

Texture &CopySource::texture() const {
  return _texture;
}

const SDL_Rect *CopySource::rect() const {
  return _rect ? &*_rect : nullptr;
}

int CopySource::width() const {
  return _rect ? _rect->w : _texture.width();
}

int CopySource::height() const {
  return _rect ? _rect->h : _texture.height();
}

CopyDest::CopyDest(const SDL_Rect &rect) : _hasDimentions{true}, _rect{rect} {
}

CopyDest::CopyDest(int x, int y) : _hasDimentions{false}, _rect{x, y, 0, 0} {
}

CopyDest::CopyDest(int x, int y, int w, int h) : CopyDest{{x, y, w, h}} {
}

SDL_Rect CopyDest::asRect(int width, int height) const {
  return {_rect.x, _rect.y, _hasDimentions ? _rect.w : width, _hasDimentions ? _rect.h : height};
}

} // namespace sdl
