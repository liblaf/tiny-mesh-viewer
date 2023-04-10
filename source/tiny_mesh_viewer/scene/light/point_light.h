#ifndef TINY_MESH_VIEWER_SCENE_POINT_LIGHT_H_
#define TINY_MESH_VIEWER_SCENE_POINT_LIGHT_H_

#include <memory>

#include "boost/signals2.hpp"
#include "glm/glm.hpp"
#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/shader/shader.h"

namespace tiny_mesh_viewer::scene {

class PointLight {
 public:
  explicit PointLight(const glm::vec3& position = kDefaultPosition,
                      const glm::vec3& color = kDefaultColor);

  void ConnectShader(shader::Shader& shader);

  glm::vec3 position() const;
  void set_position(const glm::vec3& position);
  glm::vec3 color() const;
  void set_color(const glm::vec3& color);

  boost::signals2::signal<void(const PointLight& point_light)> changed;

  static std::shared_ptr<PointLight> FromYAML(const YAML::Node& yaml);

 private:
  glm::vec3 position_;
  glm::vec3 color_;

  static constexpr glm::vec3 kDefaultPosition = glm::vec3(1.0, 1.0, -1.0);
  static constexpr glm::vec3 kDefaultColor = glm::vec3(1.0, 1.0, 1.0);
};

}  // namespace tiny_mesh_viewer::scene

#endif  // TINY_MESH_VIEWER_SCENE_POINT_LIGHT_H_
