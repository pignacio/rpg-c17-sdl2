//
// Created by Ignacio Rossi on 4/5/18.
//

#ifndef CLIONTEST_KEYBOARD_STATE_H
#define CLIONTEST_KEYBOARD_STATE_H

#include <SDL2/SDL.h>

class KeyboardState {
public:
  virtual ~KeyboardState() = default;
  bool isPressed(SDL_Scancode key) const;

  static KeyboardState create();

protected:
  KeyboardState(const Uint8 *state, int size);

private:
  const Uint8 *_state;
  const int _size;
};

#endif // CLIONTEST_KEYBOARD_STATE_H
