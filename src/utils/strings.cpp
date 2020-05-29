#include "utils/strings.hpp"

namespace utils {

auto endsWith(std::string_view haystack, std::string_view needle) -> bool {
  return needle.size() <= haystack.size() &&
         std::equal(haystack.rbegin(), haystack.rbegin() + static_cast<long>(needle.size()),
                    needle.rbegin(), needle.rend());
}

} // namespace utils
