//
// Created by Ignacio Rossi on 4/7/18.
//

#ifndef CLIONTEST_MOCK_TEXTURE_H
#define CLIONTEST_MOCK_TEXTURE_H

#include <gmock/gmock.h>

#include "sdl/texture.h"

class MockTexture : public sdl::Texture {
public:
  MOCK_CONST_METHOD0(get, SDL_Texture *());
  MOCK_CONST_METHOD0(width, int());
  MOCK_CONST_METHOD0(height, int());
};

#endif // CLIONTEST_MOCK_TEXTURE_H
