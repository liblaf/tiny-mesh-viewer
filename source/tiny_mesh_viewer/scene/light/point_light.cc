#include "tiny_mesh_viewer/scene/light/point_light.h"

#include <memory>

#include "glm/gtx/string_cast.hpp"

#include "tiny_mesh_viewer/common/config.h"
#include "tiny_mesh_viewer/common/logging.h"
#include "tiny_mesh_viewer/common/with.h"

namespace tiny_mesh_viewer::scene {

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color) {
  this->set_position(position);
  this->set_color(color);

#ifdef DEBUG_POINT_LIGHT
  this->changed.connect([](const PointLight& point_light) -> void {
    INFO("PointLight changed:");
    INFO("  position: {}", glm::to_string(point_light.position()));
    INFO("  color: {}", glm::to_string(point_light.color()));
  });
#endif  // DEBUG_POINT_LIGHT
}

void PointLight::ConnectShader(shader::Shader& shader) {
  this->changed.connect([&shader](const PointLight& point_light) -> void {
    auto with = common::WithUse(shader);
    shader.UniformVec3(/*name=*/"point_light_position",
                       /*value=*/point_light.position());
    shader.UniformVec3(/*name=*/"point_light_color",
                       /*value=*/point_light.color());
  });
}

glm::vec3 PointLight::position() const { return this->position_; }

void PointLight::set_position(const glm::vec3& position) {
  this->position_ = position;
  this->changed(*this);
}

glm::vec3 PointLight::color() const { return this->color_; }

void PointLight::set_color(const glm::vec3& color) {
  this->color_ = color;
  this->changed(*this);
}

std::shared_ptr<PointLight> PointLight::FromYAML(const YAML::Node& yaml) {
  if (!yaml.IsDefined()) return std::make_shared<PointLight>();
  return std::make_shared<PointLight>(
      /*position=*/common::Config::AsVec3(yaml["position"],
                                          /*fallback=*/kDefaultPosition),
      /*color=*/common::Config::AsVec3(yaml["color"],
                                       /*fallback=*/kDefaultColor));
}

}  // namespace tiny_mesh_viewer::scene
