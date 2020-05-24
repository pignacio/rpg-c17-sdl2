#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>

#include "data/map.h"
#include "gfx/sprite_sheet.h"
#include "logging.h"
#include "sdl/event.h"
#include "sdl/loader.h"
#include "sdl/renderer.h"
#include "sdl/window.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

using data::Map;

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 600;

class Test {
public:
  explicit Test(int x, int y) : _x{x}, _y{y} {
  }

  template <class Archive> void serialize(Archive &ar, [[gnu::unused]] uint32_t version) {
    std::cout << "serialize:Version: " << version << std::endl;
    ar(CEREAL_NVP(_x));
    if (version > 1) {
      ar(CEREAL_NVP(_y));
    }
  }

  void lala() const {
    std::cout << "Values are: " << _x << ", " << _y << std::endl;
  }

private:
  int _x;
  int _y;
};

CEREAL_CLASS_VERSION(Test, 2); // NOLINT

Map loadMap(std::istream &stream) {
  int height;
  int width;
  stream >> width >> height;
  Map map{width, height};
  return map;
}

auto getInitialMap() -> Map {
  /*  if (argc < 2) {
      filename = "/tmp/mapa.lala";
      LOG_INFO(LOG, "No filename supplied. Writing to " << filename)
      return {10, 10};
    } else {
      filename = argv[1];
      LOG_INFO(LOG, "Loading map data from " << filename)
      auto ifstream = std::ifstream{filename};
      return loadMap(ifstream);
    }*/
  return {1, 1};
}

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
  data::Map map{10, 10};
  map.set(3, 3, 3);
  map.set(6, 6, 6);

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

  std::ofstream out{"/tmp/testing_map.json"};
  cereal::JSONOutputArchive archive{out};
  archive(map);
}

auto main() -> int {
  signal(SIGSEGV, logging::terminateWithSignal);
  std::set_terminate(logging::terminate);

  LOG_INFO(LOG, "Hai!");
  run();
  LOG_INFO(LOG, "Kthxbye!");
  return 0;
}
