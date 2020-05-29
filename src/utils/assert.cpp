#include "utils/assert.hpp"

#include "logging.hpp"
namespace utils {

auto checkIndex(int index, int size, const char *name) -> void {
  LOG_ASSERT(LOG, 0 <= index && index < size,
             "Invalid index " << name << ":" << index << " (size:" << size << ")");
}

} // namespace utils
