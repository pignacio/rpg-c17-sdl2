//
// Created by Ignacio Rossi on 4/15/18.
//

#ifndef CLIONTEST_FRAME_COUNTER_H
#define CLIONTEST_FRAME_COUNTER_H

#include <chrono>

template <typename Clock> class FrameCounter {
public:
  FrameCounter() : _start{Clock::now()}, _last{_start}, _count{0} {
  }

  typename Clock::duration nextFrameDuration() {
    _count++;
    auto current = Clock::now();
    auto res = current - _last;
    _last = current;
    return res;
  }

  int getFrameCount() const {
    return _count;
  }

  double getFramesPerSecond() const {
    return 1000 * _count /
           std::chrono::duration_cast<std::chrono::milliseconds>(_last - _start).count();
  }

private:
  typename Clock::time_point _start;
  typename Clock::time_point _last;
  int _count;
};

#endif // CLIONTEST_FRAME_COUNTER_H
