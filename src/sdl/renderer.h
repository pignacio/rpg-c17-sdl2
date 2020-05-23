//
// Created by Ignacio Rossi on 4/1/18.
//

#ifndef CLIONTEST_RENDERER_H
#define CLIONTEST_RENDERER_H

#include <memory>
#include <string>
#include<optional>

#include <SDL2/SDL_render.h>

#include "surface.h"
#include "texture.h"
#include "window.h"

namespace sdl {

class CopySource;
class CopyDest;

class Renderer {
public:
  Renderer(SDL_Renderer *renderer, Window window);
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  virtual ~Renderer();

  Texture::ptr createTexture(const Surface &surface) const;

  void clear();
  void copy(const CopySource &source, const CopyDest &dest);
  void present();

  Window getWindow() const;

  static std::unique_ptr<Renderer> init(Window window, Uint32 renderer_flags);

private:
  SDL_Renderer *_renderer;
  Window _window;
};

class CopySource {
public:
  CopySource(Texture &texture);
  CopySource(Texture &texture, SDL_Rect rect);

  Texture &texture() const;
  int width() const;
  int height() const;

  const SDL_Rect *rect() const;

private:
  Texture &_texture;
  std::optional<SDL_Rect> _rect;
};

class CopyDest {
public:
  CopyDest(const SDL_Rect &rect);
  CopyDest(int x, int y);
  CopyDest(int x, int y, int w, int h);

  SDL_Rect asRect(int width, int height) const;

private:
  const bool _hasDimentions;
  const SDL_Rect _rect;
};

} // namespace sdl

#endif // CLIONTEST_RENDERER_H
