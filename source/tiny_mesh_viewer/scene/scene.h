#ifndef TINY_MESH_VIEWER_SCENE_SCENE_H_
#define TINY_MESH_VIEWER_SCENE_SCENE_H_

#include <memory>
#include <vector>

#include "tiny_mesh_viewer/scene/camera.h"
#include "tiny_mesh_viewer/scene/light/ambient_light.h"
#include "tiny_mesh_viewer/scene/light/point_light.h"
#include "tiny_mesh_viewer/scene/object/object.h"

namespace tiny_mesh_viewer::scene {

class Scene {
 public:
  explicit Scene(std::shared_ptr<Camera> camera = nullptr,
                 std::shared_ptr<AmbientLight> ambient_light = nullptr,
                 std::shared_ptr<PointLight> point_light = nullptr,
                 const std::vector<std::shared_ptr<Object>>& objects = {});

  void Draw();

  Camera& camera();
  AmbientLight& ambient_light();
  PointLight& point_light();
  std::vector<std::shared_ptr<Object>>& objects();

  static std::shared_ptr<Scene> FromYAML(const YAML::Node& yaml);

 private:
  std::shared_ptr<Camera> camera_;
  std::shared_ptr<AmbientLight> ambient_light_;
  std::shared_ptr<PointLight> point_light_;
  std::vector<std::shared_ptr<Object>> objects_;
};

}  // namespace tiny_mesh_viewer::scene

#endif  // TINY_MESH_VIEWER_SCENE_SCENE_H_
