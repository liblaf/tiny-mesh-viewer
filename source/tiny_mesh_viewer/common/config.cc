#include "tiny_mesh_viewer/common/config.h"

#include <algorithm>

#include "glm/glm.hpp"
#include "yaml-cpp/yaml.h"

namespace tiny_mesh_viewer::common {

bool Config::IsVec3(const YAML::Node& yaml) {
  return yaml.IsDefined() && yaml.IsSequence() && yaml.size() == 3 &&
         std::all_of(yaml.begin(), yaml.end(),
                     /*pred=*/[](const YAML::Node& node) -> bool {
                       return node.IsScalar();
                     });
}

glm::vec3 Config::AsVec3(const YAML::Node& yaml) {
  return Config::AsTVec3<glm::vec3::value_type>(yaml);
}

glm::vec3 Config::AsVec3(const YAML::Node& yaml, const glm::vec3& fallback) {
  return Config::AsTVec3<glm::vec3::value_type>(yaml, fallback);
}

}  // namespace tiny_mesh_viewer::common
