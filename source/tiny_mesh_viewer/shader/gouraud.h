#ifndef TINY_MESH_VIEWER_SHADER_GOURAUD_H_
#define TINY_MESH_VIEWER_SHADER_GOURAUD_H_

#include <string_view>

#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/shader/blinn_phong.h"

namespace tiny_mesh_viewer::shader {

class Gouraud : public BlinnPhong {
 public:
  explicit Gouraud();
  virtual ~Gouraud() = default;

  static std::shared_ptr<Gouraud> FromYAML(const YAML::Node& yaml);

 private:
  static constexpr std::string_view kDefaultVertexShaderFilePath =
      "shader/gouraud.vs";
  static constexpr std::string_view kDefaultFragmentShaderFilePath =
      "shader/gouraud.fs";
};

}  // namespace tiny_mesh_viewer::shader

#endif  // TINY_MESH_VIEWER_SHADER_GOURAUD_H_
