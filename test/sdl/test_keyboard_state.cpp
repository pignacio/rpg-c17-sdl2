//
// Created by Ignacio Rossi on 4/7/18.
//

#include "prelude.h"
#include "sdl/keyboard_state.h"

SDL_Scancode key(int index) {
  return static_cast<SDL_Scancode>(index);
}

class MyKeyboardState : public KeyboardState {
public:
  MyKeyboardState(Uint8 *state, int size) : KeyboardState(state, size){};
};

SCENARIO("Using a KeyboardState", "[sdl][KeyboardState]") {
  constexpr int size = 5;
  Uint8 values[size];
  memset(values, 0, sizeof(Uint8) * size);
  MyKeyboardState state{values, size};

  GIVEN("An empty state") {
    THEN("All keys resolve to false") {
      for (int i = 0; i < size; i++) {
        REQUIRE_FALSE(state.isPressed(key(i)));
      }
    }
  }

  GIVEN("Some pressed keys") {
    values[0] = values[2] = 1;

    THEN("Those keys show as pressed") {
      REQUIRE(state.isPressed(key(0)));
      REQUIRE(state.isPressed(key(2)));
    }
    AND_THEN("The other keys are not pressed") {
      REQUIRE_FALSE(state.isPressed(key(1)));
      REQUIRE_FALSE(state.isPressed(key(3)));
      REQUIRE_FALSE(state.isPressed(key(4)));
    }
  }

  GIVEN("A full keyboard state") {
    memset(values, 1, sizeof(Uint8) * size);
    THEN("Out of bound access return false ") {
      REQUIRE_FALSE(state.isPressed(key(-1)));
      REQUIRE_FALSE(state.isPressed(key(size)));
      REQUIRE_FALSE(state.isPressed(key(size + 10)));
    }
  }
}
