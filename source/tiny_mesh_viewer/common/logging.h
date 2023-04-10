#ifndef TINY_MESH_VIEWER_COMMON_LOGGING_H_
#define TINY_MESH_VIEWER_COMMON_LOGGING_H_

#include <source_location>

#include "spdlog/spdlog.h"

#ifdef __cpp_lib_source_location
namespace tiny_mesh_viewer::common {
using source_loc = std::source_location;
}
#else
#include <experimental/source_location>
namespace tiny_mesh_viewer::common {
using source_loc = std::experimental::source_location;
}
#endif  // __cpp_lib_source_location

namespace tiny_mesh_viewer::common::logging {

template <typename... Args>
void log(const source_loc &loc, const spdlog::level::level_enum level,
         spdlog::format_string_t<Args...> fmt, Args &&...args) {
  spdlog::log(
      spdlog::source_loc(loc.file_name(), loc.line(), loc.function_name()),
      level, fmt, std::forward<Args>(args)...);
}

#define INFO(fmt, ...)                                 \
  tiny_mesh_viewer::common::logging::log(              \
      tiny_mesh_viewer::common::source_loc::current(), \
      spdlog::level::level_enum::info, fmt, ##__VA_ARGS__)

#define ERROR(fmt, ...)                                \
  tiny_mesh_viewer::common::logging::log(              \
      tiny_mesh_viewer::common::source_loc::current(), \
      spdlog::level::level_enum::err, fmt, ##__VA_ARGS__)

}  // namespace tiny_mesh_viewer::common::logging

#endif  // TINY_MESH_VIEWER_COMMON_LOGGING_H_
