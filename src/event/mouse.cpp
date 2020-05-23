/*
 * mouse.cpp
 * Copyright (C) 2020 irossi <rossi.ignacio@gmail.com>
 *
 * Distributed under terms of the GPLv3 license.
 */

#include "event/mouse.h"

namespace event {

void MouseEventListener::listen(MouseEventListener::Listener listener) {
  _listeners.push_back(listener);
}

void MouseEventListener::listen(MouseEventListener::PartialListener listener) {
  listen([&listener](const MouseEvent &event, [[gnu::unused]] const MouseState &state) {
    listener(event);
  });
}

MouseState MouseEventListener::getMouseState() const {
  return _state;
}

void MouseEventListener::process(const MouseEvent &event) {
  updateState(event);
  for (auto &listener : _listeners) {
    listener(event, getMouseState());
  }
}

void MouseEventListener::updateState(const MouseEvent &event) {
  if (event.position) {
    _state.position = *event.position;
  }
  if (event.buttonUp) {
    _state.is_button_down[*event.buttonUp] = false;
  }
  if (event.buttonDown) {
    _state.is_button_down[*event.buttonDown] = true;
  }
}

} // namespace event
