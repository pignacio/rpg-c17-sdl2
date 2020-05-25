//
// Created by Ignacio Rossi on 4/1/18.
//

#ifndef CLIONTEST_PTR_H
#define CLIONTEST_PTR_H

#include "../logging.h"

#include <functional>
#include <gsl/pointers>

namespace sdl {
template <typename T> using internal_ptr = std::unique_ptr<T, std::function<void(T *)>>;

template <typename SDL_T, typename T> class sdl_unique_ptr {
public:
  sdl_unique_ptr(internal_ptr<SDL_T> ptr, std::unique_ptr<T> t)
      : _ptr{std::move(ptr)}, _wrapper{std::move(t)} {
    LOG_ASSERT(LOG, _ptr != nullptr, "Null sdl pointer");
    LOG_ASSERT(LOG, _wrapper != nullptr, "Null sdl wrapper pointer");
  }

  sdl_unique_ptr(sdl_unique_ptr &&moved) noexcept
      : _ptr{std::move(moved._ptr)}, _wrapper{std::move(moved._wrapper)} {
  }

  sdl_unique_ptr(const sdl_unique_ptr &) = delete;
  sdl_unique_ptr &operator=(const sdl_unique_ptr &) = delete;

  T &operator*() {
    return *_wrapper;
  }

  T *operator->() noexcept {
    return _wrapper.get();
  }

  SDL_T *getRaw() const {
    return _ptr.get();
  }

private:
  internal_ptr<SDL_T> _ptr;
  std::unique_ptr<T> _wrapper;
};

template <typename SDL_T, typename T>
sdl_unique_ptr<SDL_T, T> make_sdl_ptr(SDL_T *ptr, std::function<void(SDL_T *)> deleter) {
  return make_sdl_ptr<SDL_T, T>(ptr, deleter, new T(ptr));
};

template <typename SDL_T, typename T>
sdl_unique_ptr<SDL_T, T> make_sdl_ptr(SDL_T *ptr, std::function<void(SDL_T *)> deleter,
                                      gsl::owner<T *> wrapper) {
  return sdl_unique_ptr<SDL_T, T>{internal_ptr<SDL_T>{ptr, deleter}, std::unique_ptr<T>{wrapper}};
};

} // namespace sdl

#endif // CLIONTEST_PTR_H
