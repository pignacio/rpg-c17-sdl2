//
// Created by Ignacio Rossi on 4/3/18.
//

#ifndef CLIONTEST_SDLLOADER_H
#define CLIONTEST_SDLLOADER_H

#include <functional>

#include "SDL2/SDL.h"

namespace sdl {

class SdlLoader {

public:
  virtual ~SdlLoader();

  static std::unique_ptr<SdlLoader> init(Uint32 sdlFlags, int imgFlags);
};
} // namespace sdl

#endif // CLIONTEST_SDLLOADER_H
