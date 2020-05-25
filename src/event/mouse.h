/*
 * mouse.h
 * Copyright (C) 2020 irossi <rossi.ignacio@gmail.com>
 *
 * Distributed under terms of the GPLv3 license.
 */

#ifndef EVENT_LISTENER_H_
#define EVENT_LISTENER_H_

#include <functional>
#include <optional>
#include <vector>

#include "enum_array.h"
#include "point/point.h"

namespace event {

enum class MouseButton { RIGHT, MIDDLE, LEFT };

template <typename T> using MouseButtonArray = EnumArray<MouseButton, T, 3>;

struct MouseState {
  MouseButtonArray<bool> is_button_down;
  point::IPoint position;
  // TODO: window?
};

struct MouseEvent {
  std::optional<point::IPoint> position;
  std::optional<MouseButton> buttonDown;
  std::optional<MouseButton> buttonUp;
};

class MouseEventListener {
  using Listener = std::function<void(const MouseEvent &, const MouseState &)>;
  using PartialListener = std::function<void(const MouseEvent &)>;

public:
  void listen(const Listener &listener);
  void listen(PartialListener listener);
  MouseState getMouseState() const;

  void process(const MouseEvent &event);

private:
  MouseState _state;
  std::vector<Listener> _listeners;

  void updateState(const MouseEvent &event);
};

} // namespace event

#endif // EVENT_LISTENER_H_
