#ifndef TINY_MESH_VIEWER_APP_H_
#define TINY_MESH_VIEWER_APP_H_

#include <map>
#include <memory>

#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/opengl/app.h"
#include "tiny_mesh_viewer/scene/scene.h"
#include "tiny_mesh_viewer/shader/shader.h"
#include "tiny_mesh_viewer/ui/window.h"

namespace tiny_mesh_viewer {

class App : public tiny_mesh_viewer::opengl::App {
 public:
  explicit App(const YAML::Node& yaml = {});

  void Run();

  scene::Scene& scene();
  ui::Window& window();

 private:
  std::shared_ptr<scene::Scene> scene_;
  std::map<std::string, std::shared_ptr<shader::Shader> > shaders_;
  std::unique_ptr<ui::Window> window_;
};

}  // namespace tiny_mesh_viewer

#endif  // TINY_MESH_VIEWER_APP_H_
