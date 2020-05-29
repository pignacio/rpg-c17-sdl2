//
// Created by Ignacio Rossi on 5/26/18.
//

#ifndef CLIONTEST_ANIMATION_H
#define CLIONTEST_ANIMATION_H

#include "sdl/renderer.h"
#include "direction.h"

namespace gfx {

class SpriteSheet;

class ActorAnimation {
public:
  virtual ~ActorAnimation() = default;

  virtual sdl::CopySource getFrame(int ticks, const Direction& direction) = 0;
};

class ActorAnimationImpl : public ActorAnimation {
public:
  ActorAnimationImpl(SpriteSheet &_sheet, int duration);
  ActorAnimationImpl(SpriteSheet &_sheet, DirectionMap<int> indexes, int duration);

  sdl::CopySource getFrame(int ticks, const Direction& direction);

private:
  gfx::SpriteSheet &_sheet;
  DirectionMap<int> _indexes;
  int _duration;
};

} // namespace gfx
#endif
