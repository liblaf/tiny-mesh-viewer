#ifndef TINY_MESH_VIEWER_COMMON_MATH_H_
#define TINY_MESH_VIEWER_COMMON_MATH_H_

#include "glm/glm.hpp"

namespace tiny_mesh_viewer::common::math {

/** Convert yaw, pitch to a direction vector.
 *
 * @return direction vector
 */
glm::vec3 EulerToVector(const glm::vec2& euler /**< [in] yaw, pitch */);

/** Convert a direction vector to yaw, pitch.
 *
 * @return yaw, pitch
 */
glm::vec2 VectorToEuler(const glm::vec3& vector /**< [in] direction vector */);

}  // namespace tiny_mesh_viewer::common::math

#endif  // TINY_MESH_VIEWER_COMMON_MATH_H_
