/*
 * main_editor.cpp
 * Copyright (C) 2020 irossi <rossi.ignacio@gmail.com>
 *
 * Distributed under terms of the GPLv3 license.
 */

#include <fstream>
#include <iostream>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "data/map.h"
#include "event/mouse.h"
#include "gfx/sprite_sheet.h"
#include "logging.h"
#include "sdl/event.h"
#include "sdl/loader.h"
#include "sdl/renderer.h"
#include "sdl/window.h"
#include "serialization/serialization.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

sdl::Texture::ptr loadTexture(const std::string &path, sdl::Renderer *renderer) {
  auto surface = sdl::Surface::load(path)->optimizeFor(renderer->getWindow().getScreen());
  return renderer->createTexture(*surface);
}

void handleQueueEvents(const sdl::EventQueue &queue,
                       std::vector<std::function<void(sdl::Event &)>> listeners) {
  // Handle events on queue
  while (auto event = queue.poll()) {
    for (auto listener : listeners) {
      listener(*event);
    }
  }
}

void run(int argc, char *argv[]) {
  signal(SIGSEGV, logging::terminateWithSignal);
  std::set_terminate(logging::terminate);

  LOG_INFO(LOG, "I'm an editor");
  auto loader = sdl::SdlLoader::init(SDL_INIT_VIDEO, IMG_INIT_PNG);
  auto window = sdl::Window::create("My SDL App", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  auto renderer = sdl::Renderer::init(*window, SDL_RENDERER_SOFTWARE);

  // Get window surface
  auto screen = renderer->getWindow().getScreen();

  auto tiles = loadTexture("magecity.png", renderer.get());
  const int TILESIZE = 32;
  gfx::SpriteSheetImpl tile_sheet{*tiles, TILESIZE, TILESIZE};
  sdl::EventQueue queue;
  bool quit = false;
  std::string filename;
  data::Map map{10, 10};
  if (argc < 2) {
    filename = "/tmp/mapa.lala";
    LOG_INFO(LOG, "No filename supplied. Writing to " << filename)
  } else {
    filename = argv[1];
    LOG_INFO(LOG, "Loading map data from " << filename)
    auto ifstream = std::ifstream{filename};
    map = serialization::readJson<data::Map>(ifstream);
  }

  int selected_tile = 1;
  std::vector<std::function<void(sdl::Event &)>> listeners;
  event::MouseEventListener mouse_listener;

  auto updateMap = [&map, &selected_tile](const point::IPoint &position) {
    int xx = position.x / TILESIZE;
    int yy = position.y / TILESIZE;
    if (0 <= xx && xx < 10 && 0 <= yy && yy < 10) {
      map.set(xx, yy, selected_tile);
    }
  };

  // Quit events
  listeners.push_back([&quit](auto event) {
    if (event.isQuit() || event.isKeyDown(SDL_SCANCODE_ESCAPE) || event.isKeyDown(SDL_SCANCODE_Q)) {
      quit = true;
    }
  });
  listeners.push_back([&mouse_listener](auto event) {
    if (auto mouse_event = event.asMouseEvent()) {
      mouse_listener.process(*mouse_event);
    };
  });

  // Select tile events
  listeners.push_back([&tile_sheet, &selected_tile](sdl::Event &event) {
    int next_tile = selected_tile;
    if (event.isKeyDown(SDL_SCANCODE_1)) {
      next_tile = 1;
    } else if (event.isKeyDown(SDL_SCANCODE_2)) {
      next_tile = 2;
    } else if (event.isKeyDown(SDL_SCANCODE_UP)) {
      next_tile++;
    } else if (event.isKeyDown(SDL_SCANCODE_DOWN)) {
      next_tile--;
    }
    next_tile %= tile_sheet.size();
    if (next_tile < 0) {
      next_tile += tile_sheet.size();
    }
    // Not-so-atomically swap
    selected_tile = next_tile;
  });

  while (!quit) {
    handleQueueEvents(queue, listeners);

    auto state = mouse_listener.getMouseState();
    if (state.is_button_down[event::MouseButton::LEFT]) {
      updateMap(state.position);
    }

    renderer->clear();
    map.forEach([&renderer, &tile_sheet](int x, int y, int value) {
        renderer->copy(tile_sheet.get(value), {TILESIZE * x, TILESIZE * y});
    });
    renderer->copy(tile_sheet.get(selected_tile), {SCREEN_WIDTH - 2 * TILESIZE, TILESIZE});
    renderer->present();
  }
  serialization::writeJson(map, std::cout);
  serialization::writeJsonToFile(map, filename);
}

int main(int argc, char *argv[]) {
  try {
    run(argc, argv);
    return 0;
  } catch (std::runtime_error e) {
    LOG_FATAL(LOG, "Something wrong happened! " << e.what());
    return 1;
  }
}
