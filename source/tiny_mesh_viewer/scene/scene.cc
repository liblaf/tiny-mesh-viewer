#include "tiny_mesh_viewer/scene/scene.h"

#include <algorithm>
#include <memory>
#include <vector>

#include "tiny_mesh_viewer/scene/camera.h"
#include "tiny_mesh_viewer/scene/light/ambient_light.h"
#include "tiny_mesh_viewer/scene/light/point_light.h"
#include "tiny_mesh_viewer/scene/object/object.h"

namespace tiny_mesh_viewer::scene {

Scene::Scene(std::shared_ptr<Camera> camera,
             std::shared_ptr<AmbientLight> ambient_light,
             std::shared_ptr<PointLight> point_light,
             const std::vector<std::shared_ptr<Object>>& objects)
    : camera_(camera),
      ambient_light_(ambient_light),
      point_light_(point_light),
      objects_(objects) {}

void Scene::Draw() {
  std::for_each(this->objects_.begin(), this->objects_.end(),
                [](std::shared_ptr<Object> object) -> void { object->Draw(); });
}

Camera& Scene::camera() { return *(this->camera_); }

AmbientLight& Scene::ambient_light() { return *(this->ambient_light_); }

PointLight& Scene::point_light() { return *(this->point_light_); }

std::vector<std::shared_ptr<Object>>& Scene::objects() {
  return this->objects_;
}

std::shared_ptr<Scene> Scene::FromYAML(const YAML::Node& yaml) {
  if (!yaml.IsDefined()) {
    return std::make_shared<Scene>(std::make_shared<Camera>(),
                                   std::make_shared<AmbientLight>(),
                                   std::make_shared<PointLight>());
  }
  std::vector<std::shared_ptr<Object>> objects;
  if (yaml["objects"].IsDefined()) {
    std::transform(
        yaml["objects"].begin(), yaml["objects"].end(),
        /*result=*/std::back_inserter(objects),
        /*unary_op=*/[](const YAML::Node& yaml) -> std::shared_ptr<Object> {
          return Object::FromYAML(yaml);
        });
  }
  auto scene = std::make_shared<Scene>(
      Camera::FromYAML(yaml["camera"]),
      AmbientLight::FromYAML(yaml["ambient_light"]),
      PointLight::FromYAML(yaml["point_light"]), objects);
  return scene;
}

}  // namespace tiny_mesh_viewer::scene
