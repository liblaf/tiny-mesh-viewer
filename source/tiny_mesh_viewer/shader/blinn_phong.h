#ifndef TINY_MESH_VIEWER_SHADER_BLINN_PHONG_H_
#define TINY_MESH_VIEWER_SHADER_BLINN_PHONG_H_

#include <filesystem>

#include "cmrc/cmrc.hpp"

#include "tiny_mesh_viewer/shader/shader.h"

namespace tiny_mesh_viewer::shader {

class BlinnPhong : public Shader {
 public:
  explicit BlinnPhong(const std::filesystem::path& vertex_shader_filepath,
                      const std::filesystem::path& fragment_shader_filepath);
  virtual ~BlinnPhong() = default;

  /** Load additional parameters from YAML.
   */
  void LoadYAML(const YAML::Node& yaml);

 private:
  static constexpr float kDefaultAmbientReflection = 1.0;
  static constexpr float kDefaultDiffuseReflection = 1.0;
  static constexpr float kDefaultSpecularReflection = 1.0;
  static constexpr float kDefaultShininess = 80.0;
};

}  // namespace tiny_mesh_viewer::shader

#endif  // TINY_MESH_VIEWER_SHADER_BLINN_PHONG_H_
