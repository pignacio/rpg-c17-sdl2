#ifndef SRC_UTILS_STRING_H
#define SRC_UTILS_STRING_H

#include <string_view>
namespace utils {

auto endsWith(std::string_view haystack, std::string_view needle) -> bool;

} // namespace utils

#endif // SRC_UTILS_STRING_H
