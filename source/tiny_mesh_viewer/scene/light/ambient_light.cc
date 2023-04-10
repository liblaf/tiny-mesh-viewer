#include "tiny_mesh_viewer/scene/light/ambient_light.h"

#include <cassert>
#include <memory>

#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"

#include "tiny_mesh_viewer/common/config.h"
#include "tiny_mesh_viewer/common/logging.h"
#include "tiny_mesh_viewer/common/with.h"

namespace tiny_mesh_viewer::scene {

AmbientLight::AmbientLight(const glm::vec3& color) {
  this->set_color(color);

#ifdef DEBUG_AMBIENT_LIGHT
  this->changed.connect([](const AmbientLight& ambient_light) -> void {
    INFO("AmbientLight changed:");
    INFO("  color: {}", glm::to_string(ambient_light.color()));
  });
#endif  // DEBUG_AMBIENT_LIGHT
}

void AmbientLight::ConnectShader(shader::Shader& shader) {
  this->changed.connect([&shader](const AmbientLight& ambient_light) -> void {
    auto with = common::WithUse(shader);
    shader.UniformVec3("ambient_light_color", ambient_light.color());
  });
}

glm::vec3 AmbientLight::color() const { return this->color_; }

void AmbientLight::set_color(const glm::vec3& color) {
  this->color_ = color;
  this->changed(*this);
}

std::shared_ptr<AmbientLight> AmbientLight::FromYAML(const YAML::Node& yaml) {
  if (!yaml.IsDefined()) return std::make_shared<AmbientLight>();
  return std::make_shared<AmbientLight>(
      /*color=*/common::Config::AsVec3(yaml["color"],
                                       /*fallback=*/kDefaultColor));
}

}  // namespace tiny_mesh_viewer::scene
