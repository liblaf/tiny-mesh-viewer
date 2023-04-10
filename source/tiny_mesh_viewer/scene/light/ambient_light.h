#ifndef TINY_MESH_VIEWER_SCENE_AMBIENT_LIGHT_H_
#define TINY_MESH_VIEWER_SCENE_AMBIENT_LIGHT_H_

#include <memory>

#include "boost/signals2.hpp"
#include "glm/glm.hpp"
#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/shader/shader.h"

namespace tiny_mesh_viewer::scene {

class AmbientLight {
 public:
  explicit AmbientLight(const glm::vec3& color = kDefaultColor);

  void ConnectShader(shader::Shader& shader);

  glm::vec3 color() const;
  void set_color(const glm::vec3& color);

  static std::shared_ptr<AmbientLight> FromYAML(const YAML::Node& yaml);

  boost::signals2::signal<void(const AmbientLight& ambient_light)> changed;

 private:
  glm::vec3 color_;

  static constexpr glm::vec3 kDefaultColor = glm::vec3(0.25, 0.25, 0.25);
};

}  // namespace tiny_mesh_viewer::scene

#endif  // TINY_MESH_VIEWER_SCENE_AMBIENT_LIGHT_H_
