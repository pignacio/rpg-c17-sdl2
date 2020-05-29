//
// Created by Ignacio Rossi on 4/5/18.
//

#include "keyboard_state.hpp"
#include "../logging.hpp"

KeyboardState::KeyboardState(gsl::span<const Uint8> state) : _state{state} {
}

bool KeyboardState::isPressed(SDL_Scancode key) const {
  if (key < 0 || key >= _state.size()) {
    LOG_WARN(LOG, "Invalid key!: " << key);
    return false;
  }
  return _state[key];
}

KeyboardState KeyboardState::create() {
  int size = 0;
  const Uint8 *state = SDL_GetKeyboardState(&size);
  return KeyboardState({state, static_cast<size_t>(size)});
}
