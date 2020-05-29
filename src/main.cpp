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
#include "gfx/sprite_sheet.hpp"
#include "logging.hpp"
#include "sdl/event.hpp"
#include "sdl/loader.hpp"
#include "sdl/renderer.hpp"
#include "sdl/window.hpp"
#include "serialization/serialization.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

using data::Map;

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 600;

auto loadTexture(const std::string &path, sdl::Renderer *renderer) -> sdl::Texture::ptr {
  auto surface = sdl::Surface::load(path)->optimizeFor(renderer->getWindow().getScreen());
  return renderer->createTexture(*surface);
}

auto run() -> void {
  auto loader = sdl::SdlLoader::init(SDL_INIT_VIDEO, IMG_INIT_PNG);
  auto window = sdl::Window::create("My SDL App", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  auto renderer = sdl::Renderer::init(*window, SDL_RENDERER_SOFTWARE);

  // Get window surface
  auto screen = renderer->getWindow().getScreen();

  auto tiles = loadTexture("magecity.png", renderer.get());
  const int TILESIZE = 32;
  gfx::SpriteSheetImpl tile_sheet{*tiles, TILESIZE, TILESIZE};
  auto mapPath = "/tmp/testing_map";
  LOG_INFO(LOG, "Reading map from " << mapPath);
  Map map = serialization::readFromFile<Map>(mapPath).orPanic();

  bool quit = false;
  sdl::EventQueue queue;
  while (!quit) {
    while (auto event = queue.poll()) {
      if (event->isQuit() || event->isKeyDown(SDL_SCANCODE_ESCAPE) ||
          event->isKeyDown(SDL_SCANCODE_Q)) {
        quit = true;
      }
    }
    renderer->clear();
    map.forEach([&renderer, &tile_sheet](int x, int y, int value) {
      renderer->copy(tile_sheet.get(value), {TILESIZE * x, TILESIZE * y});
    });
    renderer->present();
    SDL_Delay(16);
  }

  serialization::writeBinaryToFile(map, "/tmp/testing_map");
}

auto main() -> int {
  signal(SIGSEGV, logging::terminateWithSignal);
  std::set_terminate(logging::terminate);

  LOG_INFO(LOG, "Hai!");
  run();
  LOG_INFO(LOG, "Kthxbye!");
  return 0;
}
