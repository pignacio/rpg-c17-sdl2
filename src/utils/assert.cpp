#include "utils/assert.h"

#include "logging.h"
namespace utils {

auto checkIndex(int index, int size, const char *name) -> void {
  LOG_ASSERT(LOG, 0 <= index && index < size,
             "Invalid index " << name << ":" << index << " (size:" << size << ")");
}

} // namespace utils
