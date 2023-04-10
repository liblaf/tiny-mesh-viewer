#ifndef TINY_MESH_VIEWER_COMMON_ERROR_H_
#define TINY_MESH_VIEWER_COMMON_ERROR_H_

#include <stdexcept>

#include "fmt/format.h"

#include "tiny_mesh_viewer/common/logging.h"

namespace tiny_mesh_viewer::common {

template <typename T = std::runtime_error>
class Exception : public T {
 public:
  explicit Exception(const source_loc& loc, const std::string& what)
      : T(what), loc_(loc) {}

  virtual const char* what() const noexcept override {
    this->what_ = fmt::format("[{}:{}] {}", this->loc_.file_name(),
                              this->loc_.line(), this->T::what());
    return this->what_.c_str();
  }

 private:
  source_loc loc_;
  mutable std::string what_;
};

};  // namespace tiny_mesh_viewer::common

#endif  // TINY_MESH_VIEWER_COMMON_ERROR_H_
