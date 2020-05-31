//
// Created by Ignacio Rossi on 4/5/18.
//

#ifndef CLIONTEST_KEYBOARD_STATE_H
#define CLIONTEST_KEYBOARD_STATE_H

#include <SDL2/SDL.h>
#include <gsl/span>

namespace sdl {

class KeyboardState {
public:
  bool isPressed(SDL_Scancode key) const;

  static KeyboardState create();

  static KeyboardState createForTesting(gsl::span<const Uint8> state);

private:
  explicit KeyboardState(gsl::span<const Uint8> state);

  const gsl::span<const Uint8> _state;
};

} // namespace sdl

#endif // CLIONTEST_KEYBOARD_STATE_H
