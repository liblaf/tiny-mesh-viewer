#include "tiny_mesh_viewer/ui/canvas.h"

#include <memory>

#include "tiny_mesh_viewer/common/config.h"

namespace tiny_mesh_viewer::ui {

Canvas::Canvas(const glm::vec3& color) : color_(color) {}

void Canvas::Draw() {
  this->ClearColor();
  this->Clear();

  if (this->scene_) {
    this->scene().Draw();
  }
}

void Canvas::Clear(GLbitfield mask) { glClear(mask); }

void Canvas::ClearColor() {
  glClearColor(this->color_.r, this->color_.g, this->color_.b, /*alpha=*/1.0);
}

scene::Scene& Canvas::scene() { return *(this->scene_); }

void Canvas::set_scene(std::shared_ptr<scene::Scene> scene) {
  this->scene_ = scene;
}

std::shared_ptr<Canvas> Canvas::FromYAML(const YAML::Node& yaml) {
  if (!yaml.IsDefined()) return std::make_shared<Canvas>();
  return std::make_shared<Canvas>(
      common::Config::AsVec3(yaml["color"], /*fallback=*/kDefaultColor));
}

}  // namespace tiny_mesh_viewer::ui
