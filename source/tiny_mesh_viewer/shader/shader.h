#ifndef TINY_MESH_VIEWER_SHADER_SHADER_H_
#define TINY_MESH_VIEWER_SHADER_SHADER_H_

#include <memory>

#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/opengl/program.h"

namespace tiny_mesh_viewer::shader {

class Shader : public tiny_mesh_viewer::opengl::Program {
 public:
  explicit Shader() = default;
  virtual ~Shader() = default;

  static std::shared_ptr<Shader> FromYAML(const YAML::Node& yaml);
};

};  // namespace tiny_mesh_viewer::shader

#endif  // TINY_MESH_VIEWER_SHADER_SHADER_H_
