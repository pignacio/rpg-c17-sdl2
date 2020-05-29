#ifndef SERIALIZATION_SERIALIZATION_H
#define SERIALIZATION_SERIALIZATION_H

#include <fstream>
#include <istream>
#include <string>

#include <boost/type_index.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <gsl/string_span>

#include "logging.hpp"
#include "serialization/result.hpp"
#include "utils/strings.hpp"

namespace serialization {
namespace internal {

constexpr gsl::czstring<> JSON_SUFFIX = ".json";
constexpr gsl::czstring<> BINARY_SUFFIX = ".bin";

template <typename Data, typename Archive> auto read(std::istream &stream) -> Result<Data> {
  try {
    auto data = Data::emptyValue();
    Archive archive{stream};
    archive(data);
    return Result{data};
  } catch (std::runtime_error e) {
    return Result<Data>::error(e.what());
  }
}

template <typename Data, typename Archive> auto readFile(const std::string &path) -> Result<Data> {
  LOG_INFO(LOG, "Reading " << boost::typeindex::type_id<Data>().pretty_name() << " from " << path
                           << " using " << boost::typeindex::type_id<Archive>().pretty_name());
  std::ifstream stream{path};
  if (!stream.good()) {
    return Result<Data>::error("Could not read from file '" + path + "'");
  }
  return read<Data, Archive>(stream);
}

template <typename Data, typename Archive> auto write(const Data &data, std::ostream &stream) {
  Archive archive{stream};
  archive(data);
}

template <typename Data, typename Archive>
auto writeToFile(const Data &data, const std::string &path, const std::string &suffix) -> void {
  auto finalPath = utils::endsWith(path, suffix) ? path : path + suffix;
  LOG_INFO(LOG, "Writing " << boost::typeindex::type_id<Data>().pretty_name() << " to " << finalPath
                           << " using " << boost::typeindex::type_id<Archive>().pretty_name());
  std::ofstream stream{finalPath};
  write<Data, Archive>(data, stream);
}

} // namespace internal

template <typename Data> auto readFromFile(const std::string &path) -> Result<Data> {
  if (utils::endsWith(path, internal::JSON_SUFFIX) && std::ifstream{path}.good()) {
    return internal::readFile<Data, cereal::JSONInputArchive>(path);
  } else if (utils::endsWith(path, internal::BINARY_SUFFIX) && std::ifstream{path}.good()) {
    return internal::readFile<Data, cereal::PortableBinaryInputArchive>(path);
  } else if (auto jsonPath = path + internal::JSON_SUFFIX; std::ifstream{jsonPath}.good()) {
    return internal::readFile<Data, cereal::JSONInputArchive>(jsonPath);
  } else if (auto binaryPath = path + internal::BINARY_SUFFIX; std::ifstream{binaryPath}.good()) {
    return internal::readFile<Data, cereal::PortableBinaryInputArchive>(binaryPath);
  }
  return Result<Data>::error("Could not read data. Tried in files: " + path + "{,.bin,.json}");
}

template <typename Data> auto readJson(std::istream &stream) -> Result<Data> {
  return internal::read<Data, cereal::JSONInputArchive>(stream);
}

template <typename Data> auto readBinary(std::istream &stream) -> Result<Data> {
  return internal::read<Data, cereal::PortableBinaryInputArchive>(stream);
}

template <typename Data> auto writeBinaryToFile(const Data &data, const std::string &path) -> void {
  internal::writeToFile<Data, cereal::PortableBinaryOutputArchive>(data, path,
                                                                   internal::BINARY_SUFFIX);
}

template <typename Data> auto writeJsonToFile(const Data &data, const std::string &path) -> void {
  internal::writeToFile<Data, cereal::JSONOutputArchive>(data, path, internal::JSON_SUFFIX);
}

template <typename Data> auto writeJson(const Data &data, std::ostream &stream) {
  internal::write<Data, cereal::JSONOutputArchive>(data, stream);
}

template <typename Data> auto writeBinary(const Data &data, std::ostream &stream) {
  internal::write<Data, cereal::PortableBinaryOutputArchive>(data, stream);
}

} // namespace serialization

#endif // SERIALIZATION_SERIALIZATION_H
