#ifndef TINY_MESH_VIEWER_UI_CANVAS_H_
#define TINY_MESH_VIEWER_UI_CANVAS_H_

#include <memory>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/scene/scene.h"

namespace tiny_mesh_viewer::ui {

class Canvas {
 public:
  Canvas(const glm::vec3& color = kDefaultColor);
  void Draw();

  void Clear(GLbitfield mask = GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  void ClearColor();

  scene::Scene& scene();
  void set_scene(std::shared_ptr<scene::Scene> scene);

  static std::shared_ptr<Canvas> FromYAML(const YAML::Node& yaml);

 private:
  std::shared_ptr<scene::Scene> scene_;
  glm::vec3 color_;

  static constexpr glm::vec3 kDefaultColor =
      glm::vec3(0.0, 101.0 / 255.0, 179.0 / 255.0);
};

}  // namespace tiny_mesh_viewer::ui

#endif  // TINY_MESH_VIEWER_UI_CANVAS_H_
