#ifndef TINY_MESH_VIEWER_COMMON_CONFIG_H_
#define TINY_MESH_VIEWER_COMMON_CONFIG_H_

#include "glm/glm.hpp"
#include "yaml-cpp/yaml.h"

namespace tiny_mesh_viewer::common {

class Config {
 public:
  static bool IsVec3(const YAML::Node& yaml);

  template <typename T = float, glm::qualifier Q = glm::defaultp>
  static glm::tvec3<T, Q> AsTVec3(const YAML::Node& yaml) {
    return glm::tvec3<T, Q>(yaml[0].as<T>(), yaml[1].as<T>(), yaml[2].as<T>());
  }

  template <typename T = float, glm::qualifier Q = glm::defaultp>
  static glm::tvec3<T, Q> AsTVec3(const YAML::Node& yaml,
                                  const glm::tvec3<T, Q>& fallback) {
    try {
      return glm::tvec3<T, Q>(yaml[0].as<T>(fallback[0]),
                              yaml[1].as<T>(fallback[1]),
                              yaml[2].as<T>(fallback[2]));
    } catch (...) {
      return fallback;
    }
  }

  static glm::vec3 AsVec3(const YAML::Node& yaml);
  static glm::vec3 AsVec3(const YAML::Node& yaml, const glm::vec3& fallback);
};

}  // namespace tiny_mesh_viewer::common

#endif  // TINY_MESH_VIEWER_COMMON_CONFIG_H_
