#include "actor_animation.h"

#include "gfx/sprite_sheet.h"
#include "logging.h"

namespace gfx {

DirectionMap<int> defaultIndexes() {
  DirectionMap<int> indexes;
  indexes[Direction::LEFT] = 0;
  indexes[Direction::LEFT_UP] = 0;
  indexes[Direction::UP] = 1;
  indexes[Direction::UP_RIGHT] = 1;
  indexes[Direction::DOWN] = 2;
  indexes[Direction::DOWN_LEFT] = 2;
  indexes[Direction::RIGHT] = 3;
  indexes[Direction::RIGHT_DOWN] = 3;
    // Fallback to right
  indexes[Direction::NONE] = 3;
  return indexes;
}

ActorAnimationImpl::ActorAnimationImpl(SpriteSheet &sheet, int duration)
    : ActorAnimationImpl{sheet, defaultIndexes(), duration} {}

ActorAnimationImpl::ActorAnimationImpl(SpriteSheet &sheet, DirectionMap<int> indexes, int duration)
    : _sheet{sheet}, _indexes{indexes}, _duration{duration} {
  LOG_ASSERT(LOG, duration > 0, "Duration must be positive");
  LOG_ASSERT(LOG, _sheet.height() >= 4, "Sprite sheet must be at least 4 tall");
}

sdl::CopySource ActorAnimationImpl::getFrame(int ticks, const Direction& direction) {
  int index = (ticks / _duration) % _sheet.width();
  return {_sheet.get(index, _indexes[direction])};
}

} // namespace gfx
