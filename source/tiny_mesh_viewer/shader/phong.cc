#include "tiny_mesh_viewer/shader/phong.h"

#include <memory>

#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/common/with.h"
#include "tiny_mesh_viewer/shader/blinn_phong.h"

namespace tiny_mesh_viewer::shader {

Phong::Phong()
    : BlinnPhong(kDefaultVertexShaderFilePath, kDefaultFragmentShaderFilePath) {
}

std::shared_ptr<Phong> Phong::FromYAML(const YAML::Node& yaml) {
  auto shader = std::make_shared<Phong>();
  auto with = common::WithUse(*shader);
  shader->LoadYAML(yaml);
  return shader;
}

}  // namespace tiny_mesh_viewer::shader
