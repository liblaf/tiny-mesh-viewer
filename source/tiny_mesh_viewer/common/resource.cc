#include "tiny_mesh_viewer/common/resource.h"

#include <filesystem>
#include <string>

#include "cmrc/cmrc.hpp"

CMRC_DECLARE(resource);

namespace tiny_mesh_viewer::common {

auto fs = cmrc::resource::get_filesystem();

cmrc::file Resource::Open(const std::filesystem::path &filepath) {
  return fs.open(filepath.string());
}

}  // namespace tiny_mesh_viewer::common
