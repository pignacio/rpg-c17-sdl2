//
// Created by Ignacio Rossi on 4/4/18.
//

#ifndef CLIONTEST_EVENT_H
#define CLIONTEST_EVENT_H

#include <optional>

#include <SDL2/SDL.h>

#include "event/mouse.hpp"
#include "ptr.hpp"

namespace sdl {

class Event {
public:
  explicit Event();

  bool isKeyDown(SDL_Scancode key) const;
  bool isKeyUp(SDL_Scancode key) const;
  bool isMouseMovement(int &x, int &y) const;
  bool isQuit() const;
  std::optional<event::MouseEvent> asMouseEvent() const;

  SDL_Event *get();

private:
  SDL_Event _event;
};

class EventQueue {
public:
  std::optional<Event> poll() const;
};

} // namespace sdl

#endif // CLIONTEST_EVENT_H
