//
// Created by Ignacio Rossi on 4/5/18.
//

#include "keyboard_state.h"
#include "../logging.h"

KeyboardState::KeyboardState(const Uint8 *state, int size) : _state{state}, _size{size} {
}

bool KeyboardState::isPressed(SDL_Scancode key) const {
  if (key < 0 || key >= _size) {
    LOG_WARN(LOG, "Invalid key!: " << key);
    return false;
  }
  return _state[key];
}

KeyboardState KeyboardState::create() {
  int size;
  const Uint8 *state = SDL_GetKeyboardState(&size);
  return KeyboardState(state, size);
}
