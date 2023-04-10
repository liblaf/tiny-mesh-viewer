#include "tiny_mesh_viewer/common/math.h"

#include "glm/glm.hpp"

namespace tiny_mesh_viewer::common::math {

glm::vec3 EulerToVector(const glm::vec2& euler) {
  float yaw = euler[0];
  float pitch = euler[1];
  return glm::vec3{/*x=*/glm::sin(yaw) * glm::cos(pitch), /*y=*/glm::sin(pitch),
                   /*z=*/glm::cos(yaw) * glm::cos(pitch)};
}

glm::vec2 VectorToEuler(const glm::vec3& vector) {
  glm::vec3 v = glm::normalize(vector);
  float pitch = glm::asin(v.y);
  float sin_yaw = v.x / glm::cos(pitch);
  float cos_yaw = glm::clamp<float>(v.z / glm::cos(pitch), /*minVal=*/-1.0,
                                    /*maxVal=*/+1.0);
  float yaw = glm::acos(cos_yaw);
  if (sin_yaw < 0) {
    yaw = -yaw;
  }
  return glm::vec2(yaw, pitch);
}

}  // namespace tiny_mesh_viewer::common::math
