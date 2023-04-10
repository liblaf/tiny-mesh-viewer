#include "tiny_mesh_viewer/shader/gouraud.h"

#include <memory>

#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/common/with.h"
#include "tiny_mesh_viewer/shader/blinn_phong.h"

namespace tiny_mesh_viewer::shader {

Gouraud::Gouraud()
    : BlinnPhong(kDefaultVertexShaderFilePath, kDefaultFragmentShaderFilePath) {
}

std::shared_ptr<Gouraud> Gouraud::FromYAML(const YAML::Node& yaml) {
  auto shader = std::make_shared<Gouraud>();
  auto with = common::WithUse(*shader);
  shader->LoadYAML(yaml);
  return shader;
}

}  // namespace tiny_mesh_viewer::shader
