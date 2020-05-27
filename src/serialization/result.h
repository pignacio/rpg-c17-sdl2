#ifndef SRC_SERIALIZATION_RESULT_H
#define SRC_SERIALIZATION_RESULT_H

#include <optional>
#include <string>
#include <string_view>

namespace serialization {

template <typename Data> class Result {
public:
  explicit Result(Data data) : _result{data}, _message{} {};

  static auto error(std::string_view message) -> Result<Data> {
    return Result{message};
  };

  auto orThrow(std::function<std::runtime_error(const std::string &)> errorSupplier) -> Data {
    if (_result) {
      return *_result;
    } else {
      throw errorSupplier(_message);
    }
  }

  auto orPanic() -> Data {
    return orThrow([](const std::string &message) { return std::runtime_error{message}; });
  }

private:
  explicit Result(std::string_view message) : _result{}, _message(message) {};

  std::optional<Data> _result;
  std::string _message;
};

} // namespace serialization

#endif // SRC_SERIALIZATION_RESULT_H
