//
// Created by Ignacio Rossi on 4/7/18.
//

#include "prelude.h"
#include "sdl/keyboard_state.h"

SDL_Scancode key(int index) {
  return static_cast<SDL_Scancode>(index);
}

KeyboardState createStateForTesting(gsl::span<const Uint8> state) {
  return KeyboardState{state};
}

SCENARIO("Using a KeyboardState", "[sdl][KeyboardState]") {
  constexpr int size = 5;
  std::array<Uint8, size> values{};
  auto state = createStateForTesting(values);

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
    memset(values.data(), 1, sizeof(Uint8) * size);
    THEN("Out of bound access return false ") {
      REQUIRE_FALSE(state.isPressed(key(-1)));
      REQUIRE_FALSE(state.isPressed(key(size)));
      REQUIRE_FALSE(state.isPressed(key(size + 10)));
    }
  }
}
