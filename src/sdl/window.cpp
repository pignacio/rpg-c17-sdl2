//
// Created by Ignacio Rossi on 4/1/18.
//

#include "window.h"
#include "../logging.h"

namespace sdl {

Window::Window(SDL_Window *window) : _window(window) {
}

Surface Window::getScreen() const {
  return Surface(SDL_GetWindowSurface(_window));
}

SDL_Window *Window::get() const {
  return _window;
}

void Window::free(SDL_Window *window) {
  LOG_INFO(LOG, "Destroying SDL_Window[" << window << "]");
  SDL_DestroyWindow(window);
}

Window::ptr Window::wrap(SDL_Window *window) {
  LOG_INFO(LOG, "Wrapping Window[" << window << "]");
  return sdl::make_sdl_ptr<SDL_Window, Window>(window, &Window::free);
}

Window::ptr Window::create(const std::string &window_title, int width, int height,
                           Uint32 window_flags) {
  LOG_INFO(LOG, "Creating SDL window. Resolution: " << width << "x" << height
                                                    << ". Flags: " << window_flags);
  auto window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, width, height, window_flags);
  LOG_ASSERT(LOG, window != nullptr,
             "Could not create window: SDL_Error: '" << SDL_GetError() << "'");
  return Window::wrap(window);
}

std::ostream &operator<<(std::ostream &stream, const Window &window) {
  return stream << "Window[" << window.get() << "]";
}
} // namespace sdl
