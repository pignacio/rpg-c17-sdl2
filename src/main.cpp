#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>

#include "data/map.hpp"
#include "direction.hpp"
#include "frame_counter.hpp"
#include "gfx/actor_animation.hpp"
#include "gfx/sprite_sheet.hpp"
#include "logging.hpp"
#include "point/point.hpp"
#include "sdl/event.hpp"
#include "sdl/keyboard_state.hpp"
#include "sdl/loader.hpp"
#include "sdl/renderer.hpp"
#include "sdl/window.hpp"
#include "serialization/serialization.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

using data::Map;
using point::DPoint;
using point::IPoint;
using sdl::KeyboardState;

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 600;

auto loadTexture(const std::string &path, sdl::Renderer *renderer) -> sdl::Texture::ptr {
  auto surface = sdl::Surface::load(path)->optimizeFor(renderer->getWindow().getScreen());
  return renderer->createTexture(*surface);
}

constexpr SDL_Scancode movementKeys[] = {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT,
                                         SDL_SCANCODE_RIGHT};

std::map<SDL_Scancode, DPoint> movementSpeeds = {
    {SDL_SCANCODE_UP, {0, -1}},
    {SDL_SCANCODE_DOWN, {0, 1}},
    {SDL_SCANCODE_LEFT, {-1, 0}},
    {SDL_SCANCODE_RIGHT, {1, 0}},
};

void update(long long elapsed, Direction &direction, DPoint &position) {
  double linearSpeed = .3 * elapsed;
  DPoint speed{0, 0};
  KeyboardState keys = KeyboardState::create();
  for (auto key : movementKeys) {
    if (keys.isPressed(key)) {
      speed += movementSpeeds[key];
    }
  }
  Direction newDirection = Direction::getDirection(speed);
  if (newDirection != Direction::NONE) {
    direction = newDirection;
  }
  position += speed * linearSpeed;
}

auto run() -> void {
  auto loader = sdl::SdlLoader::init(SDL_INIT_VIDEO, IMG_INIT_PNG);
  auto window = sdl::Window::create("My SDL App", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  auto renderer = sdl::Renderer::init(*window, SDL_RENDERER_SOFTWARE);

  // Get window surface
  auto screen = renderer->getWindow().getScreen();

  // Load tileset + map
  auto tiles = loadTexture("magecity.png", renderer.get());
  const int TILESIZE = 32;
  gfx::SpriteSheetImpl tile_sheet{*tiles, TILESIZE, TILESIZE};
  auto mapPath = "/tmp/testing_map";
  LOG_INFO(LOG, "Reading map from " << mapPath);
  Map map = serialization::readFromFile<Map>(mapPath).orPanic();

  // Load hero animation
  auto hero = loadTexture("hero.png", renderer.get());
  gfx::SpriteSheetImpl heroSheet{*hero, 32, 36};

  DirectionMap<int> indexes;
  indexes[Direction::UP] = 0;
  indexes[Direction::UP_RIGHT] = 0;
  indexes[Direction::RIGHT] = 1;
  indexes[Direction::RIGHT_DOWN] = 1;
  indexes[Direction::DOWN] = 2;
  indexes[Direction::DOWN_LEFT] = 2;
  indexes[Direction::LEFT] = 3;
  indexes[Direction::LEFT_UP] = 3;
  // Fallback to right
  indexes[Direction::NONE] = 1;

  gfx::ActorAnimationImpl heroAnimation{heroSheet, indexes, 90};

  bool quit = false;
  sdl::EventQueue queue;
  DPoint position{0, 0};
  Direction direction = Direction::RIGHT;
  FrameCounter<steady_clock> counter;
  steady_clock::duration unprocessed = nanoseconds{0};
  int totalTicks = 0;
  while (!quit) {
    while (auto event = queue.poll()) {
      if (event->isQuit() || event->isKeyDown(SDL_SCANCODE_ESCAPE) ||
          event->isKeyDown(SDL_SCANCODE_Q)) {
        quit = true;
      }
    }

    unprocessed += counter.nextFrameDuration();
    auto elapsed = duration_cast<milliseconds>(unprocessed).count();
    unprocessed -= milliseconds{elapsed};
    totalTicks += elapsed;
    LOG_INFO(LOG, "Elapsed : " << elapsed << ". Unprocessed remainder: "
                               << duration_cast<nanoseconds>(unprocessed).count() << "ns");

    update(elapsed, direction, position);

    renderer->clear();
    map.forEach([&renderer, &tile_sheet](int x, int y, int value) {
      renderer->copy(tile_sheet.get(value), {TILESIZE * x, TILESIZE * y});
    });
    renderer->copy(heroAnimation.getFrame(totalTicks, direction), position.cast<int>());
    renderer->present();
    SDL_Delay(16);
  }

  serialization::writeBinaryToFile(map, "/tmp/testing_map");
}

auto main() -> int {
  signal(SIGSEGV, logging::terminateWithSignal);
  std::set_terminate(logging::terminate);

  LOG_INFO(LOG, "Hai!");
  try {
    run();
  } catch (std::runtime_error e) {
    LOG_FATAL(LOG, "run() failed :(. " << e.what());
  }
  LOG_INFO(LOG, "Kthxbye!");
  return 0;
}
