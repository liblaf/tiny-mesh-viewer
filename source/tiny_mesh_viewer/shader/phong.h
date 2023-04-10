#ifndef TINY_MESH_VIEWER_SHADER_PHONG_H_
#define TINY_MESH_VIEWER_SHADER_PHONG_H_

#include "tiny_mesh_viewer/shader/blinn_phong.h"
#include "tiny_mesh_viewer/shader/shader.h"

namespace tiny_mesh_viewer::shader {

class Phong : public BlinnPhong {
 public:
  explicit Phong();
  virtual ~Phong() = default;

  static std::shared_ptr<Phong> FromYAML(const YAML::Node& yaml);

 private:
  static constexpr std::string_view kDefaultVertexShaderFilePath =
      "shader/phong.vs";
  static constexpr std::string_view kDefaultFragmentShaderFilePath =
      "shader/phong.fs";
};

}  // namespace tiny_mesh_viewer::shader

#endif  // TINY_MESH_VIEWER_SHADER_PHONG_H_
