/*
 * test_logging.cpp
 * Copyright (C) 2018 irossi <rossi.ignacio@gmail.com>
 *
 * Distributed under terms of the GPLv3 license.
 */

#include "logging.hpp"
#include "prelude.hpp"

SCENARIO("dumpBacktrace works without an exception", "[logging]") {
  GIVEN("No current exception") {
    THEN("dumpBacktrace() does not crash") {
      logging::dumpBacktrace();
    }
  }
  GIVEN("A thrown exception") {
    THEN("dumpBacktrace() does not crash") {
      try {
        throw std::runtime_error{"test"};
      } catch (...) {
        logging::dumpBacktrace();
      }
    }
  }
}
