#define CATCH_CONFIG_RUNNER

#include "logging.h"
#include "prelude.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

int main(int argc, char **argv) {
  auto start = steady_clock::now();
  ::testing::GTEST_FLAG(throw_on_failure) = true;
  ::testing::InitGoogleMock(&argc, argv);
  auto res = Catch::Session().run(argc, argv);
  auto end = steady_clock::now();
  LOG_INFO(LOG, "Testing took " << duration_cast<milliseconds>(end - start).count() << " ms.")
  return res;
}
