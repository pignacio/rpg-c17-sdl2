#ifndef SERIALIZATION_SERIALIZATION_H
#define SERIALIZATION_SERIALIZATION_H

#include <fstream>
#include <istream>
#include <string>

#include <boost/type_index.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <gsl/string_span>

#include "logging.h"

namespace serialization {

constexpr gsl::czstring<> JSON_SUFFIX = ".json";
constexpr gsl::czstring<> BINARY_SUFFIX = ".bin";

auto endsWith(std::string_view haystack, std::string_view needle) -> bool {
  return needle.size() <= haystack.size() &&
         std::equal(haystack.rbegin(), haystack.rbegin() + static_cast<long>(needle.size()),
                    needle.rbegin(), needle.rend());
}

template <typename Data, typename Archive> auto read(const std::string &path) -> Data {
  LOG_INFO(LOG, "Reading " << boost::typeindex::type_id<Data>().pretty_name() << " from " << path
                           << " using " << boost::typeindex::type_id<Archive>().pretty_name());
  auto data = Data::emptyValue();
  std::ifstream stream{path};
  Archive archive{stream};
  archive(data);
  return data;
}

template <typename Data> auto readFromFile(const std::string &path) -> Data {
  if (endsWith(path, JSON_SUFFIX) && std::ifstream{path}.good()) {
    return read<Data, cereal::JSONInputArchive>(path);
  } else if (endsWith(path, BINARY_SUFFIX) && std::ifstream{path}.good()) {
    return read<Data, cereal::PortableBinaryInputArchive>(path);
  } else if (auto jsonPath = path + JSON_SUFFIX; std::ifstream{jsonPath}.good()) {
    return read<Data, cereal::JSONInputArchive>(jsonPath);
  } else if (auto binaryPath = path + BINARY_SUFFIX; std::ifstream{binaryPath}.good()) {
    return read<Data, cereal::PortableBinaryInputArchive>(binaryPath);
  }
  throw "TODO: better error handling";
}

template <typename Data, typename Archive>
auto writeToFile(const Data &data, const std::string &path, const std::string &suffix) -> void {
  auto finalPath = endsWith(path, suffix) ? path : path + suffix;
  LOG_INFO(LOG, "Writing " << boost::typeindex::type_id<Data>().pretty_name() << " to " << finalPath
                           << " using " << boost::typeindex::type_id<Archive>().pretty_name());
  std::ofstream stream{finalPath};
  Archive archive{stream};
  archive(data);
}

template <typename Data> auto writeBinaryToFile(const Data &data, const std::string &path) -> void {
  writeToFile<Data, cereal::PortableBinaryOutputArchive>(data, path, BINARY_SUFFIX);
}

template <typename Data> auto writeJsonToFile(const Data &data, const std::string &path) -> void {
  writeToFile<Data, cereal::JSONOutputArchive>(data, path, JSON_SUFFIX);
}

} // namespace serialization

#endif // SERIALIZATION_SERIALIZATION_H
