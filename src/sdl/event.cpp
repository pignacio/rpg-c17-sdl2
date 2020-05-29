//
// Created by Ignacio Rossi on 4/4/18.
//

#include "event.hpp"

namespace sdl {

Event::Event() : _event{} {
}

SDL_Event *Event::get() {
  return &_event;
}

bool Event::isKeyDown(SDL_Scancode key) const {
  return _event.type == SDL_KEYDOWN && _event.key.keysym.scancode == key;
}

bool Event::isKeyUp(SDL_Scancode key) const {
  return _event.type == SDL_KEYUP && _event.key.keysym.scancode == key;
}

bool Event::isMouseMovement(int &x, int &y) const {
  if (_event.type == SDL_MOUSEMOTION) {
    x = _event.motion.x;
    y = _event.motion.y;
    return true;
  }
  return false;
}

bool Event::isQuit() const {
  return _event.type == SDL_QUIT;
}

std::optional<event::MouseEvent> Event::asMouseEvent() const {
  event::MouseEvent event;
  switch (_event.type) {
  case SDL_MOUSEMOTION: {
    event.position = {_event.motion.x, _event.motion.y};
    return event;
  }
  case SDL_MOUSEBUTTONUP:
  case SDL_MOUSEBUTTONDOWN: {
    auto &buttonState = (_event.type == SDL_MOUSEBUTTONUP) ? event.buttonUp : event.buttonDown;
    buttonState = {_event.button.button == SDL_BUTTON_LEFT ? event::MouseButton::LEFT
                                                           : event::MouseButton::RIGHT};
    event.position = {_event.button.x, _event.button.y};
    return event;
  }
  default: {
    return std::nullopt;
  }
  }
}

std::optional<Event> EventQueue::poll() const {
  Event event;
  return SDL_PollEvent(event.get()) != 0 ? std::optional<Event>{event} : std::nullopt;
}

} // namespace sdl
