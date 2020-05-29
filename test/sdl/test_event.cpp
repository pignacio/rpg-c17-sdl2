//
// Created by Ignacio Rossi on 4/7/18.
//

#include "prelude.hpp"
#include "sdl/event.hpp"

using sdl::Event;

SCENARIO("Events work correctly", "[sdl][Event]") {
  Event event{};
  SDL_Event *sdl_event = event.get();

  GIVEN("A quit event") {
    sdl_event->type = SDL_QUIT;
    THEN("it trigger isQuit().") {
      REQUIRE(event.isQuit());
    }
    AND_THEN("it does not trigger isKeyUp") {
      REQUIRE_FALSE(event.isKeyUp(SDL_SCANCODE_A));
      REQUIRE_FALSE(event.isKeyUp(SDL_SCANCODE_Q));
    }
    AND_THEN("it does not trigger isKeyDown") {
      REQUIRE_FALSE(event.isKeyDown(SDL_SCANCODE_A));
      REQUIRE_FALSE(event.isKeyDown(SDL_SCANCODE_Q));
    }
  }

  GIVEN("A key down event") {
    sdl_event->type = SDL_KEYDOWN;
    sdl_event->key.keysym.scancode = SDL_SCANCODE_A;
    THEN("it does not trigger isQuit().") {
      REQUIRE_FALSE(event.isQuit());
    }
    AND_THEN("it does not trigger isKeyUp") {
      REQUIRE_FALSE(event.isKeyUp(SDL_SCANCODE_A));
      REQUIRE_FALSE(event.isKeyUp(SDL_SCANCODE_Q));
    }
    AND_THEN("it triggers isKeyDown for the correct key") {
      REQUIRE(event.isKeyDown(SDL_SCANCODE_A));
    }
    AND_THEN("it does not trigger isKeyDown for the incorrect key") {
      REQUIRE_FALSE(event.isKeyDown(SDL_SCANCODE_Q));
    }
  }

  GIVEN("A key up event") {
    sdl_event->type = SDL_KEYUP;
    sdl_event->key.keysym.scancode = SDL_SCANCODE_A;
    THEN("it does not trigger isQuit().") {
      REQUIRE_FALSE(event.isQuit());
    }
    AND_THEN("it triggers isKeyUp for the correct key") {
      REQUIRE(event.isKeyUp(SDL_SCANCODE_A));
    }
    AND_THEN("it does not trigger isKeyUp for the incorrect key") {
      REQUIRE_FALSE(event.isKeyUp(SDL_SCANCODE_Q));
    }
    AND_THEN("it does not trigger isKeyDown") {
      REQUIRE_FALSE(event.isKeyDown(SDL_SCANCODE_A));
      REQUIRE_FALSE(event.isKeyDown(SDL_SCANCODE_Q));
    }
  }
}
