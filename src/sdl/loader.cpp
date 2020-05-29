//
// Created by Ignacio Rossi on 4/3/18.
//

#include "loader.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../logging.hpp"

namespace sdl {

SdlLoader::~SdlLoader() {
  LOG_INFO(LOG, "Quitting SDL_ttf");
  TTF_Quit();
  LOG_INFO(LOG, "Quitting SDL_image");
  IMG_Quit();
  LOG_INFO(LOG, "Quitting SDL");
  SDL_Quit();
}

std::unique_ptr<SdlLoader> SdlLoader::init(Uint32 sdlFlags, int imgFlags) {
  LOG_INFO(LOG, "Initializing SDL")
  if (SDL_Init(sdlFlags) < 0) {
    LOG_THROW(LOG, "Could not initialize SDL!");
  }
  LOG_INFO(LOG, "Initializing SDL_image")
  int inited = IMG_Init(imgFlags);
  if (!(inited & imgFlags)) {
    LOG_THROW(LOG, "Could not initialize SDL_image! Tried: " << imgFlags << " but got: " << inited);
  }
  LOG_INFO(LOG, "Initializing SDL_ttf")
  if (TTF_Init() < 0) {
    LOG_THROW(LOG, "Could not initialize SDL_ttf!");
  }
  return std::make_unique<SdlLoader>();
}
} // namespace sdl
