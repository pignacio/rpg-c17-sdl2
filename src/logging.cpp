//
// Created by Ignacio Rossi on 4/2/18.
//

#include "logging.h"
#include <execinfo.h>
#include <unistd.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

namespace logging {

void terminateWithSignal([[gnu::unused]] int signal) {
  terminate();
}

void terminate() {
  dumpBacktrace();
  abort();
}

void dumpBacktrace() {
  auto eptr = std::current_exception();
  if (eptr) {
    try {
      std::rethrow_exception(eptr);
    } catch (const std::exception &e) {
      fprintf(stderr, "A wild exception appears! what(): '%s'\n", e.what());
    }
  }
  fprintf(stderr, "Last SDL_Error: '%s'\n", SDL_GetError());
  fprintf(stderr, "Last IMG_Error: '%s'\n", IMG_GetError());
  fprintf(stderr, "Last TTF_Error: '%s'\n", TTF_GetError());
  void *array[30];   // NOLINT
  auto size = backtrace(array, 30);  // NOLINT
  fprintf(stderr, "<backtrace>\n");
  backtrace_symbols_fd(array + 2, size - 2, STDERR_FILENO);  // NOLINT
  fprintf(stderr, "</backtrace>\n");
}

} // namespace logging
