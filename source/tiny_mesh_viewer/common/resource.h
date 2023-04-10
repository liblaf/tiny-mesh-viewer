#ifndef TINY_MESH_VIEWER_COMMON_RESOURCE_H_
#define TINY_MESH_VIEWER_COMMON_RESOURCE_H_

#include <filesystem>

#include "cmrc/cmrc.hpp"

namespace tiny_mesh_viewer::common {

class Resource {
 public:
  static cmrc::file Open(const std::filesystem::path& filepath);
};

}  // namespace tiny_mesh_viewer::common

#endif  // TINY_MESH_VIEWER_COMMON_RESOURCE_H_
